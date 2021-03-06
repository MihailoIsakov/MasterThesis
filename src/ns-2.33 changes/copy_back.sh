#!/bin/sh

NS_ROOT="../../ns-allinone-2.33/ns-2.33/"

cp Makefile.in $NS_ROOT"."
cp Makefile $NS_ROOT"."

cp packet.h $NS_ROOT"common/"

# routing folders are copied
cp -rf gpsr $NS_ROOT
cp -rf greedy $NS_ROOT
cp -rf goafr $NS_ROOT

# content of support folder is copied
cp support/* $NS_ROOT"/common/."

cp cmu-trace.h $NS_ROOT"/trace/."
cp cmu-trace.cc $NS_ROOT"/trace/."

cp gls_evaluate.pl $NS_ROOT"/hls/utils/."
cp run.tcl $NS_ROOT"/hls/utils/."
cp greedy_test.tcl $NS_ROOT"/hls/utils/."
cp goafr_test.tcl $NS_ROOT"/hls/utils/."
cp hls.tcl $NS_ROOT"/hls/utils/."

cp hls.cc $NS_ROOT"/hls/."
cp hls.h $NS_ROOT"/hls/."
cp hls_advanced.cc $NS_ROOT"/hls/."
cp hls_basic.cc $NS_ROOT"/hls/."
cp hls_basic.h $NS_ROOT"/hls/."

cp ns_tcl.cc $NS_ROOT"/gen/."
cp ptypes.cc $NS_ROOT"/gen/."

cp gpsr.tcl $NS_ROOT"/tcl/mobility/."

cp ns-lib.tcl $NS_ROOT"/tcl/lib/."
cp ns-packet.tcl $NS_ROOT"/tcl/lib/."
cp ns-default.tcl $NS_ROOT"/tcl/lib/."
cp ns-mobilenode.tcl $NS_ROOT"/tcl/lib/."

cp gridlocservice.cc $NS_ROOT"/locservices/."
cp realocservice.cc $NS_ROOT"/locservices/."

# copy the tcl parameters to the right folder
cp greedy.tcl $NS_ROOT"/tcl/mobility/."
cp goafr.tcl $NS_ROOT"/tcl/mobility/."

#cp commen_routing.h $NS_ROOT"/."

#temp - only here to fix a minor one off issue
cp errmodel.cc $NS_ROOT"/queue/."
cp sctp-cmt.cc $NS_ROOT"/sctp/."

cd $NS_ROOT
configure
make