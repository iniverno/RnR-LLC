
##  Copyright 2000-2007 Virtutech AB
##  
##  The contents herein are Source Code which are a subset of Licensed
##  Software pursuant to the terms of the Virtutech Simics Software
##  License Agreement (the "Agreement"), and are being distributed under
##  the Agreement.  You should have received a copy of the Agreement with
##  this Licensed Software; if not, please contact Virtutech for a copy
##  of the Agreement prior to using this Licensed Software.
##  
##  By using this Source Code, you agree to be bound by all of the terms
##  of the Agreement, and use of this Source Code is subject to the terms
##  the Agreement.
##  
##  This Source Code and any derivatives thereof are provided on an "as
##  is" basis.  Virtutech makes no warranties with respect to the Source
##  Code or any derivatives thereof and disclaims all implied warranties,
##  including, without limitation, warranties of merchantability and
##  fitness for a particular purpose and non-infringement.

from cli import *
from sim_commands import new_info_command

device_name = get_last_loaded_module()

PA_MASK =  0x1ffffffe000L

#
# -------------------- chmmu-regs --------------------
#

def sfmmu_regs_cmd(obj):
    true_false = ("false", "true")
    try:
	reg_ctx_prim = obj.ctxt_primary
        reg_ctx_sec =  obj.ctxt_secondary
	reg_ctx_nuc =  obj.ctxt_nucleus
	reg_lsu =      obj.lsu_ctrl
    
	reg_isfsr =    obj.isfsr
	reg_itsb8k =   obj.itsbp8k
	reg_itsb64k =  obj.itsbp64k
	reg_itsb =     obj.itsb
	reg_itag_acc = obj.itag_access
	reg_itag_tgt = obj.itag_target
	
        reg_dsfar =    obj.dsfar
        reg_dsfsr =    obj.dsfsr
        reg_dtsb8k =   obj.dtsbp8k
        reg_dtsb64k =  obj.dtsbp64k
        reg_dtsbpd =   obj.dtsbpd
        reg_dtsb =     obj.dtsb
        reg_dtag_acc = obj.dtag_access
        reg_dtag_tgt = obj.dtag_target

    except Exception, msg:
	print "Error reading MMU registers: %s" % msg
	return

    print "Context registers:"
    print "  Primary ctxt:   0x%04x   Secondary ctxt: 0x%04x   Nucleus ctxt:   0x%04x   " % (
	reg_ctx_prim & 0x1fff, reg_ctx_sec & 0x1fff, reg_ctx_nuc & 0x1fff)

    print "LSU control register: 0x%016x" % reg_lsu

    print ("  D-MMU enable:   %s    D-cache enable: %s"
           % (true_false[int((reg_lsu >> 3) & 1)],
              true_false[int((reg_lsu >> 1) & 1)]))
    
    print ("  I-MMU enable:   %s    I-cache enable: %s"
           % (true_false[int((reg_lsu >> 2) & 1)],
              true_false[int((reg_lsu >> 0) & 1)]))

    print "D-MMU sync fault status register:"
    print "  asi: 0x%02x  ft: 0x%02x  e: %d  ct: %d  pr: %d  w: %d ow: %d fv: %d" % (
	(reg_dsfsr >> 16) & 0xff,
	(reg_dsfsr >> 7) & 0x7f,
	(reg_dsfsr >> 6) & 1,
	(reg_dsfsr >> 4) & 3,
	(reg_dsfsr >> 3) & 1,
	(reg_dsfsr >> 2) & 1,
	(reg_dsfsr >> 1) & 1,
	(reg_dsfsr >> 0) & 1)
    
    print "I-MMU sync fault status register:"
    print "  asi: 0x%02x  ft: 0x%02x  e: %d  ct: %d  pr: %d  w: %d ow: %d fv: %d" % (
	(reg_isfsr >> 16) & 0xff,
	(reg_isfsr >> 7) & 0x7f,
	(reg_isfsr >> 6) & 1,
	(reg_isfsr >> 4) & 3,
	(reg_isfsr >> 3) & 1,
	(reg_isfsr >> 2) & 1,
	(reg_isfsr >> 1) & 1,
	(reg_isfsr >> 0) & 1)
        
    print "D-MMU sync fault address register:"
    print "  va: 0x%016x" % reg_dsfar

    print "D-MMU tag access register:"
    print ("  va: 0x%016x  context: 0x%04x"
           % (reg_dtag_acc & 0xffffffffffffe000L, int(reg_dtag_acc & 0x1fffL)))

    print "I-MMU tag access register:"
    print ("  va: 0x%016x  context: 0x%04x"
           % (reg_itag_acc & 0xffffffffffffe000L, int(reg_itag_acc & 0x1fffL)))

    print "D tsbp8k     0x%016x    I tsbp8k     0x%016x" % (reg_dtsb8k, reg_itsb8k)
    print "D tsbp64k    0x%016x    I tsbp64k    0x%016x" % (reg_dtsb64k, reg_itsb64k)
    print "D tsbpd      0x%016x                        " % (reg_dtsbpd)
    print "D tsb        0x%016x    I tsb        0x%016x" % (reg_dtsb, reg_itsb)
    print "D tag_target 0x%016x    I tag_target 0x%016x" % (reg_dtag_tgt, reg_itag_tgt)


def print_tlb_header():
    print "  # CTXT  ------- VA -------  V SZ NFO IE ------- PA -------  L CP CV  E P W G U"

#
# -------------------- d-tlb, i-tlb ------------------
#
def dump_tlb_entry(i, daccess, tagread):
    used = (daccess >> 41) & 1
    print "%3d %04x  0x%016x  %d  %d  %d  %d  0x%016x  %d  %d  %d  %d %d %d %d %d" % (
	i,
	int(tagread & 0x1fffL),
	(tagread & 0xffffffffffffe000L),
	(daccess >> 63) & 1,
	(daccess >> 61) & 3,
	(daccess >> 60) & 1,
	(daccess >> 59) & 1,
	(daccess & PA_MASK),
	(daccess >> 6) & 1,
	(daccess >> 5) & 1,
	(daccess >> 4) & 1,
	(daccess >> 3) & 1,
	(daccess >> 2) & 1,
	(daccess >> 1) & 1,
	(daccess >> 0) & 1,
	used)

def sfmmu_dtlb_cmd(obj):
    dtlb_dacc_regs = obj.dtlb_daccess
    dtlb_tags_regs = obj.dtlb_tagread
    print "  ==== D-TLB ===="
    print_tlb_header()
    for i in range(len(dtlb_dacc_regs)):
        dump_tlb_entry(i, dtlb_dacc_regs[i], dtlb_tags_regs[i])


def sfmmu_itlb_cmd(obj):
    itlb_dacc_regs = obj.itlb_daccess
    itlb_tags_regs = obj.itlb_tagread
    print "  ==== I-TLB ===="
    print_tlb_header()
    for i in range(len(itlb_dacc_regs)):
        dump_tlb_entry(i, itlb_dacc_regs[i], itlb_tags_regs[i])


#
# ----------------- d-probe, i-probe -----------------
#

def sfmmu_probe_cmd(obj, la, tlb):
    if la[0] not in ["", "v"]:
	print "Only virtual addresses can be translated"
	return
    try:
        if tlb == 0:
            (pa, idx) = obj.d_translation[la[1]]
        else:
            (pa, idx) = obj.i_translation[la[1]]
    except Exception, msg:
	print "No translation found in the MMU: %s" % msg
	return
    print
    if idx == ((1L << 64) - 1): # 64-bit '-1'
        print "1:1 translation (MMU disabled)"
    else:
        if tlb == 0:
            print "Translation found in the D-TLB"
            tlb_dacc_regs = obj.dtlb_daccess[idx]
            tlb_tags_regs = obj.dtlb_tagread[idx]
        else:
            print "Translation found in the I-TLB"
            tlb_dacc_regs = obj.itlb_daccess[idx]
            tlb_tags_regs = obj.itlb_tagread[idx]
        print
        print_tlb_header()
        dump_tlb_entry(idx, tlb_dacc_regs, tlb_tags_regs)
    print
    print "VA = 0x%016x  ->  PA = 0x%016x" % (la[1], pa)

def sfmmu_dprobe_cmd(obj, la):
    sfmmu_probe_cmd(obj, la, 0)

def sfmmu_iprobe_cmd(obj, la):
    sfmmu_probe_cmd(obj, la, 1)

#
# -------------------- trace --------------------
#

def sfmmu_trace_cmd(obj):
    old = obj.trace

    if old == 0:
        obj.trace = 1
	print "%s: turning trace bit ON" % obj.name
    else:
        obj.trace = 0
	print "%s: turning trace bit OFF" % obj.name

#
# ----------------- reverse-lookup -------------------
#

reverse_found = 0

def reverse_search(pa, tlb_name, tlb_dacc_regs, tlb_tags_regs):
    global reverse_found
    first = 1
    for i in range(len(tlb_dacc_regs)):
        mmu_pa = tlb_dacc_regs[i] & PA_MASK
        mmu_sz = 1 << (13 + 3 * ((tlb_dacc_regs[i] >> 61) & 3))
        if (mmu_pa <= pa) and (pa < (mmu_pa + mmu_sz)) and ((tlb_dacc_regs[i] >> 63) & 1) == 1:
            if first == 1:
                first = 0
                print
                print "The following entries in the %s-TLB match:" % tlb_name
                print
                print_tlb_header()
            reverse_found = 1
            dump_tlb_entry(i, tlb_dacc_regs[i], tlb_tags_regs[i])

def reverse_cmd(obj, pa):
    global reverse_found
    if pa[0] not in ["", "p"]:
	print "Only physical addresses can be translated"
	return
    pa = pa[1]
    reverse_found = 0
    # D-TLB
    tlb_dacc_regs = obj.dtlb_daccess
    tlb_tags_regs = obj.dtlb_tagread
    reverse_search(pa, "D", tlb_dacc_regs, tlb_tags_regs)
    # I-TLB
    tlb_dacc_regs = obj.itlb_daccess
    tlb_tags_regs = obj.itlb_tagread
    reverse_search(pa, "I", tlb_dacc_regs, tlb_tags_regs)

    if reverse_found == 0:
        print "No reverse translation found."

#
# ----------------- command declarations -----------------
#

new_command("regs", sfmmu_regs_cmd,
            [],
            alias = "",
            type  = "%s commands" % device_name,
            short = "print mmu registers",
            namespace = device_name,
            doc = """
Print the content of the %s MMU registers<br/>
""" % device_name, filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="257")

new_command("d-tlb", sfmmu_dtlb_cmd,
            [],
            alias = "",
            type  = "%s commands" % device_name,
            short = "print data TLB contents",
            namespace = device_name,
            see_also = ["<%s>." % device_name + 'd-probe'],
            doc = """
print the content of the data TLB<br/>
""", filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="267")

new_command("i-tlb", sfmmu_itlb_cmd,
            [],
            alias = "",
            type  = "%s commands" % device_name,
            short = "print instruction TLB contents",
            namespace = device_name,
            doc_with = "<%s>.d-tlb" % device_name, filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="278")

new_command("d-probe", sfmmu_dprobe_cmd,
            [arg(addr_t, "address") ],
            alias = "",
            type  = "%s commands" % device_name,
            short = "check data TLB for translation",
            namespace = device_name,
            see_also = ["<%s>." % device_name + 'd-tlb'],
            doc = """
Translate a virtual address to physical<br/>
The translation is based on the mappings in the
instruction or data TLB.<br/>
""", filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="286")
    
new_command("i-probe", sfmmu_iprobe_cmd,
            [arg(addr_t, "address")],
            alias = "",
            type  = "%s commands" % device_name,
            short = "check instruction TLB for translation",
            namespace = device_name,
            doc_with = "<%s>.d-probe" % device_name, filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="299")

new_command("trace", sfmmu_trace_cmd,
            [],
            alias = "",
            type  = "%s commands" % device_name,
            short = "toggle trace functionality",
            namespace = device_name,
            doc = """
Toggles trace mode<br/>
When active, lists all changes to TLB entries and to MMU registers.<br/>
""", filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="307")

new_command("reverse-lookup", reverse_cmd,
            [arg(addr_t, "address") ],
            alias = "",
            type  = "%s commands" % device_name,
            short = "check TLBs for reverse translation",
            namespace = device_name,
            see_also = ["<%s>." % device_name + 'd-probe'],
            doc = """
List mappings in all TLBs that matches the specified physical address<br/>
""", filename="/mp/simics-3.0/src/devices/spitfire-mmu/commands.py", linenumber="318")


#
# ----------------- info command -----------------
#

def get_info(obj):
    return [(None,
             [('CPU', obj.cpu)])]

new_info_command(device_name, get_info)
