/*
 * The olsr.org Optimized Link-State Routing daemon(olsrd)
 * Copyright (c) 2015
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in
 *   the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of olsr.org, olsrd nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * Visit http://www.olsr.org for more information.
 *
 * If you find this software useful feel free to make a donation
 * to the project. For more information see the website or contact
 * the copyright holders.
 *
 */

#ifndef _OLSRD_LIB_INFO_INFO_TYPES_H_
#define _OLSRD_LIB_INFO_INFO_TYPES_H_

#include <stdbool.h>

#include "common/autobuf.h"

/* these provide all of the runtime status info */
#define SIW_NEIGHBORS 0x0001
#define SIW_LINKS 0x0002
#define SIW_ROUTES 0x0004
#define SIW_HNA 0x0008
#define SIW_MID 0x0010
#define SIW_TOPOLOGY 0x0020
#define SIW_GATEWAYS 0x0040
#define SIW_INTERFACES 0x0080
#define SIW_2HOP 0x0100
#define SIW_SGW 0x0200
#define SIW_RUNTIME_ALL (SIW_NEIGHBORS | SIW_LINKS | SIW_ROUTES | SIW_HNA | SIW_MID | SIW_TOPOLOGY | SIW_GATEWAYS | SIW_INTERFACES | SIW_2HOP | SIW_SGW)
#define SIW_NEIGHBORS_FREIFUNK (SIW_NEIGHBORS | SIW_LINKS) /* special */

/* these only change at olsrd startup */
#define SIW_VERSION 0x0400
#define SIW_CONFIG 0x0800
#define SIW_PLUGINS 0x1000
#define SIW_STARTUP_ALL (SIW_VERSION | SIW_CONFIG | SIW_PLUGINS)

/* this is everything in normal format */
#define SIW_ALL (SIW_RUNTIME_ALL | SIW_STARTUP_ALL)

/* this data is not normal format but olsrd.conf format */
#define SIW_OLSRD_CONF 0x2000

typedef void (*init_plugin)(const char *plugin_name);
typedef bool (*determine_command)(const char *str, unsigned int siw);
typedef const char * (*mime_type)(unsigned int send_what);
typedef void (*output_start_end)(struct autobuf *abuf);
typedef void (*printer_neighbors)(struct autobuf *abuf, bool list_2hop);
typedef void (*printer_generic)(struct autobuf *abuf);

typedef struct {
    init_plugin init;
    determine_command is_command;
    mime_type determine_mime_type;
    output_start_end output_start;
    output_start_end output_end;
    printer_neighbors neighbors;
    printer_generic links;
    printer_generic routes;
    printer_generic topology;
    printer_generic hna;
    printer_generic mid;
    printer_generic gateways;
    printer_generic sgw;
    printer_generic version;
    printer_generic olsrd_conf;
    printer_generic interfaces;
    printer_generic config;
    printer_generic plugins;
} info_plugin_functions_t;

typedef struct {
    union olsr_ip_addr accept_ip;
    union olsr_ip_addr listen_ip;
    int ipc_port;
    int nompr;
    bool http_headers;
    bool allow_localhost;
    int ipv6_only;
} info_plugin_config_t;

#define INFO_PLUGIN_CONFIG_PLUGIN_PARAMETERS \
  { .name = "port", .set_plugin_parameter = &set_plugin_port, .data = &config.ipc_port }, \
  { .name = "accept", .set_plugin_parameter = &set_plugin_ipaddress, .data = &config.accept_ip }, \
  { .name = "listen", .set_plugin_parameter = &set_plugin_ipaddress, .data = &config.listen_ip }, \
  { .name = "httpheaders", .set_plugin_parameter = &set_plugin_boolean, .data = &config.http_headers }, \
  { .name = "allowlocalhost", .set_plugin_parameter = &set_plugin_boolean, .data = &config.allow_localhost }, \
  { .name = "ipv6only", .set_plugin_parameter = &set_plugin_boolean, .data = &config.ipv6_only }

  #endif /* _OLSRD_LIB_INFO_INFO_TYPES_H_ */