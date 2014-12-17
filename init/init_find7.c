/*
   Copyright (c) 2014, The CyanogenMod Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/fs.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

static void import_kernel_nv(char *name, int for_emulator)
{
    char *value = strchr(name, '=');
    int name_len = strlen(name);

    if (value == 0) return;
    *value++ = 0;
    if (name_len == 0) return;

    if (!strcmp(name, "oppo.pcb_version")) {
        if (!strcmp(value, "20") ||
                !strcmp(value, "21") ||
                !strcmp(value, "22") ||
                !strcmp(value, "23")) {
            property_set("ro.oppo.device", "find7s");
        } else {
            property_set("ro.oppo.device", "find7a");
        }
    }
}

static bool has_unified_layout() {
    uint64_t size=0;
    const char* datadevice="/dev/block/mmcblk0p15";

    int fd=open(datadevice, O_RDONLY);
    if (fd < 0 ) {
        // fprintf(stderr, "could not open %s for reading: %s\n", datadevice, strerror(errno));
        return false;
    }
    if (ioctl(fd, BLKGETSIZE64, &size) < 0) {
        // fprintf(stderr, "could not determine size of %s: %s\n", datadevice, strerror(errno));
        close(fd);
        return false;
    }
    close(fd);
    if (size > 4*(10^9)) { // if the data partition is larger than 4GB we probably have Coldbird's unified layout
        return true;
    }
    return false;
}

static void set_oppo_layout()
{
    if (has_unified_layout()) {
        property_set("ro.oppo.layout", "unified");
    } else {
        property_set("ro.oppo.layout", "standard");
    }
}

void vendor_load_properties()
{
    import_kernel_cmdline(0, import_kernel_nv);
    set_oppo_layout();
}
