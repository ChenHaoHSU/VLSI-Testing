/**********************************************************************/
/*  Parallel-Fault Event-Driven Transition Delay Fault Simulator      */
/*                                                                    */
/**********************************************************************/

#include "atpg.h"
#include <cassert>

/* pack 16 faults into one packet.  simulate 16 faults togeter. 
 * the following variable name is somewhat misleading */
#define num_of_pattern 16

void ATPG::transition_delay_fault_simulation() {
  int i;
  int current_detect_num = 0;
  int total_detect_num = 0;

  // debug = 1;

  /* for every vector */
  for (i = vectors.size() - 1; i >= 0; i--) {
    tdfsim_a_vector(vectors[i], current_detect_num);
    total_detect_num += current_detect_num;
    fprintf(stdout, "vector[%d] detects %d faults (%d)\n", i, current_detect_num, total_detect_num);
  }


  /* print results */
  fprintf(stdout, "\n# Result:\n");
  fprintf(stdout, "-----------------------\n");
  fprintf(stdout, "# total transition delay faults: %d\n", num_of_gate_fault);
  fprintf(stdout, "# total detected faults: %d\n", total_detect_num);
  fprintf(stdout, "# fault coverage: %f %%\n", ((double)total_detect_num/(double)num_of_gate_fault)*100);
}

void ATPG::tdfsim_a_vector(const string& vec, int& current_detect_num) {
  wptr w,faulty_wire;
  /* array of 16 fptrs, which points to the 16 faults in a simulation packet  */
  fptr simulated_fault_list[num_of_pattern];
  fptr f;
  int fault_type;
  int i,start_wire_index, nckt;
  int num_of_fault;
  
  num_of_fault = 0;

  tdfsim_good_sim(vec, true);

  for (auto pos = flist_undetect.cbegin(); pos != flist_undetect.cend(); ++pos) {
    f = *pos;
    if (f->detect == REDUNDANT) { continue;} /* ignore redundant faults */ 

    if (f->fault_type != sort_wlist[f->to_swlist]->value) {

	    /* if f is a primary output or is directly connected to an primary output
	     * the fault is detected */
      if ((f->node->type == OUTPUT) ||
	        (f->io == GO && sort_wlist[f->to_swlist]->flag & OUTPUT)) {
        f->detect = TRUE;
      }
      else {
      
        /* if f is an gate output fault */
        if (f->io == GO) {
      
	        /* if this wire is not yet marked as faulty, mark the wire as faulty
	         * and insert the corresponding wire to the list of faulty wires. */
	        if (!(sort_wlist[f->to_swlist]->flag & FAULTY)) {
	          sort_wlist[f->to_swlist]->flag |= FAULTY;
            wlist_faulty.push_front(sort_wlist[f->to_swlist]);
	        }
      
          /* add the fault to the simulated fault list and inject the fault */
          simulated_fault_list[num_of_fault] = f;
          inject_fault_value(sort_wlist[f->to_swlist], num_of_fault, f->fault_type); 
	    
	        /* mark the wire as having a fault injected 
	         * and schedule the outputs of this gate */
          sort_wlist[f->to_swlist]->flag |= FAULT_INJECTED;
          for (auto pos_n = sort_wlist[f->to_swlist]->onode.cbegin(), end_n = sort_wlist[f->to_swlist]->onode.cend(); pos_n != end_n; ++pos_n) {
            (*pos_n)->owire.front()->flag |= SCHEDULED;
          }
	    
          /* increment the number of simulated faults in this packet */
          num_of_fault++;
          /* start_wire_index keeps track of the smallest level of fault in this packet.
           * this saves simulation time.  */
          start_wire_index = min(start_wire_index, f->to_swlist);
        }  // if gate output fault
	    
        /* the fault is a gate input fault */
        else {
	    
	        /* if the fault is propagated, set faulty_wire equal to the faulty wire.
	         * faulty_wire is the gate output of f.  */
          faulty_wire = get_faulty_wire(f, fault_type);
	        if (faulty_wire != nullptr) {
	      
            /* if the faulty_wire is a primary output, it is detected */
            if (faulty_wire->flag & OUTPUT) {
              f->detect = TRUE;
            }
            else {
		          /* if faulty_wire is not already marked as faulty, mark it as faulty
		           * and add the wire to the list of faulty wires. */
		          if (!(faulty_wire->flag & FAULTY)) {
		            faulty_wire->flag |= FAULTY;
                wlist_faulty.push_front(faulty_wire);
		          }
		  
              /* add the fault to the simulated list and inject it */
              simulated_fault_list[num_of_fault] = f;
              inject_fault_value(faulty_wire, num_of_fault, fault_type);
		  
		          /* mark the faulty_wire as having a fault injected 
		           *  and schedule the outputs of this gate */
		          faulty_wire->flag |= FAULT_INJECTED;
              for (auto pos_n = faulty_wire->onode.cbegin(), end_n = faulty_wire->onode.cend(); pos_n != end_n; ++pos_n) {
                (*pos_n)->owire.front()->flag |= SCHEDULED;
              }
		   
              num_of_fault++;
              start_wire_index = min(start_wire_index, f->to_swlist);
              }
          }
        }
      } // if  gate input fault
    } // if fault is active
  }

}

void ATPG::tdfsim_good_sim(const string& vec, const bool is_v1) {
  int i, nckt;
  for(i = 0; i < cktin.size(); i++) {
    if (is_v1)
      cktin[i]->value = ctoi(vec[i]);
    else { // v2
      if (i == 0)
        cktin[i]->value = ctoi(vec.back());
      else
        cktin[i]->value = ctoi(vec[i-1]);
    }
  }

  /* initialize the circuit - mark all inputs as changed and all other
   * nodes as unknown (2) */
  nckt = sort_wlist.size();
  for (i = 0; i < nckt; i++) {
    if (i < cktin.size()) {
      sort_wlist[i]->flag |= CHANGED;
    }
    else {
      sort_wlist[i]->value = U;
    }
  }

  sim(); /* do a fault-free simulation, see sim.c */
  if (debug) { display_io(); }

  /* expand the fault-free 0,1,2 value into 32 bits (2 = unknown)  
   * and store it in wire_value1 (good value) and wire_value2 (faulty value)*/
  for (i = 0; i < nckt; i++) {
    switch (sort_wlist[i]->value) {
    case 1: sort_wlist[i]->wire_value1 = ALL_ONE;  // 11 represents logic one
            sort_wlist[i]->wire_value2 = ALL_ONE; break;
    case 2: sort_wlist[i]->wire_value1 = 0x55555555; // 01 represents unknown
            sort_wlist[i]->wire_value2 = 0x55555555; break;
    case 0: sort_wlist[i]->wire_value1 = ALL_ZERO; // 00 represents logic zero
            sort_wlist[i]->wire_value2 = ALL_ZERO; break;
    }
  } // for i
}
