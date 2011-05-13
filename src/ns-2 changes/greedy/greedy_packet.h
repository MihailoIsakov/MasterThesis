/* -*- Mode:C++; c-basic-offset: 2; tab-width:2; indent-tabs-width:t -*- 
 * Copyright (C) 2005 State University of New York, at Binghamton
 * All rights reserved.
 *
 * NOTICE: This software is provided "as is", without any warranty,
 * including any implied warranty for merchantability or fitness for a
 * particular purpose.  Under no circumstances shall SUNY Binghamton
 * or its faculty, staff, students or agents be liable for any use of,
 * misuse of, or inability to use this software, including incidental
 * and consequential damages.

 * License is hereby given to use, modify, and redistribute this
 * software, in whole or in part, for any commercial or non-commercial
 * purpose, provided that the user agrees to the terms of this
 * copyright notice, including disclaimer of warranty, and provided
 * that this copyright notice, including disclaimer of warranty, is
 * preserved in the source code and documentation of anything derived
 * from this software.  Any redistributor of this software or anything
 * derived from this software assumes responsibility for ensuring that
 * any parties to whom such a redistribution is made are fully aware of
 * the terms of this license and disclaimer.
 *
 * Author: Ke Liu, CS Dept., State University of New York, at Binghamton 
 * October, 2005
 *
 * GPSR code for NS2 version 2.26 or later
 * Note: this implementation of GPSR is different from its original 
 *       version wich implemented by Brad Karp, Harvard Univ. 1999
 *       It is not guaranteed precise implementation of the GPSR design
 */

/* gpsr_packet.h : the definition the gpsr routing protocol packet header
 *
 * hdr_hello : hello message header, broadcast to one hop neighbors
 * hdr_query : query message header, flood the data sink info into networks 
 * hdr_data  : not a really data packet header, it is just used to 
 *             be attached to any data packet created by higher layer apps
 *             The reason to use this type of header is decided by the 
 *             design of the GPSR: each data packet has to carry the 
 *             location info of its data sink, maintain the routing protocol
 *             stateless.
 */

#ifndef GREEDY_PACKET_H_
#define GREEDY_PACKET_H_

#include "packet.h"
#include <math.h>

#define SINK_TRACE_FILE "sink_trace.tr"
#define NB_TRACE_FILE "greedynb_trace.tr"

#define GREEDY_CURRENT Scheduler::instance().clock()
#define INFINITE_DELAY 5000000000000.0

#define GREEDYTYPE_HELLO  0x01   //hello msg
#define GREEDYTYPE_QUERY  0x02   //query msg from the sink
#define GREEDYTYPE_DATA   0x04   //the CBR data msg

#define GREEDY_MODE_GF    0x01   //greedy forwarding mode
#define GREEDY_MODE_PERI  0x02   //perimeter routing mode

#define HDR_GREEDY(p)   ((struct hdr_greedy*)hdr_greedy::access(p))
#define HDR_GREEDY_HELLO(p) ((struct hdr_greedy_hello*)hdr_greedy::access(p))
#define HDR_GREEDY_QUERY(p) ((struct hdr_greedy_query*)hdr_greedy::access(p))
#define HDR_GREEDY_DATA(p) ((struct hdr_greedy_data*)hdr_greedy::access(p))

struct hdr_greedy {
  u_int8_t type_;
  
  static int offset_;
  inline static int& offset() {return offset_;}
  inline static struct hdr_greedy* access(const Packet *p){
    return (struct hdr_greedy*) p->access(offset_);
  }
};


struct hdr_greedy_hello {
  u_int8_t type_;
  float x_;     //My geo info
  float y_;
  inline int size(){
    int sz =
      sizeof(u_int8_t) +
      2*sizeof(float);
    return sz;
  }
};

struct hdr_greedy_query {
  u_int8_t type_;
  float x_;      //The sink geo info
  float y_;
  float ts_;     //time stampe
  int hops_;
  u_int8_t seqno_;     //query sequence number
  inline int size(){
    int sz =
      2*sizeof(u_int8_t) +
      3*sizeof(float) +
      sizeof(int);
    return sz;
  }
};

struct hdr_greedy_data {
  u_int8_t type_;
  u_int8_t mode_;  //Greedy forwarding or Perimeter Routing

  float sx_;      //the geo info of src
  float sy_;
  float dx_;      //the geo info of dst 
  float dy_;
  float ts_;      //the originating time stamp
  inline int size(){
    int sz =
      2*sizeof(u_int8_t) +
      5*sizeof(float);
    return sz;
  }
};

union hdr_all_greedy {
  hdr_greedy       gh;
  hdr_greedy_hello ghh;
  hdr_greedy_query gqh;
  hdr_greedy_data  gdh;
};



#endif
