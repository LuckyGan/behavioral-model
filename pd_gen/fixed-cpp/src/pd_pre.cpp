/* Copyright 2013-present Barefoot Networks, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * Srikrishna Gopu (krishna@barefootnetworks.com)
 * Antonin Bas (antonin@barefootnetworks.com)
 *
 */

#include "pd/pd_pre.h"
#include "pd/pd_static.h"
#include "pd_conn_mgr.h"

extern pd_conn_mgr_t *conn_mgr_state;

extern "C" {

p4_pd_status_t mc_create_session(p4_pd_sess_hdl_t *sess_hdl) {
  (void) sess_hdl;
  return 0;
}

p4_pd_status_t mc_delete_session(p4_pd_sess_hdl_t sess_hdl) {
  (void) sess_hdl;
  return 0;
}

p4_pd_status_t mc_mgrp_create(
  p4_pd_sess_hdl_t session, int8_t device,
  mgrp_id_t mgid, mc_mgrp_hdl_t *mgrp_hdl
) {
  (void) session;
  *mgrp_hdl = pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_mgrp_create(mgid);
  return 0; // TODO
}

p4_pd_status_t mc_mgrp_destroy(
  p4_pd_sess_hdl_t session, int8_t device, mc_mgrp_hdl_t mgrp_hdl
) {
  (void) session;
  pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_mgrp_destroy(mgrp_hdl);
  return 0; // TODO
}

p4_pd_status_t mc_l1_node_create(
  p4_pd_sess_hdl_t session, int8_t device,
  mgrp_rid_t rid, mc_l1_node_hdl_t *l1_hdl
) {
  (void) session;
  *l1_hdl = pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l1_node_create(rid);
  return 0; // TODO
}

p4_pd_status_t mc_l1_associate_node(
  p4_pd_sess_hdl_t session, int8_t device,
  mc_mgrp_hdl_t mgrp_hdl, mc_l1_node_hdl_t l1_hdl
) {
  (void) session;
  pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l1_node_associate(mgrp_hdl, l1_hdl);
  return 0; // TODO
}

p4_pd_status_t mc_l1_node_destroy(
  p4_pd_sess_hdl_t session, int8_t device, mc_l1_node_hdl_t l1_hdl
) {
  (void) session;
  pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l1_node_destroy(l1_hdl);
  return 0; // TODO
}

namespace {

std::string convert_map(const uint8_t *input, const size_t size) {
  std::string output(size, '0');
  for(size_t i = 0; i < size; i++) {
    uint8_t byte = input[i / 8];
    int offset = i % 8;
    if(byte & (1 << offset)) {
      output[i] = '1';
    }
  }
  return output;
}

}

p4_pd_status_t mc_l2_node_create(
  p4_pd_sess_hdl_t session, int8_t device,
  mc_l1_node_hdl_t l1_hdl, const uint8_t *port_map,
  const uint8_t *lag_map, mc_l2_node_hdl_t *l2_hdl
) {
  (void) session; (void) lag_map;
  std::string port_map_ = convert_map(port_map, PRE_PORTS_MAX);
  *l2_hdl = pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l2_node_create(l1_hdl, port_map_);
  return 0; // TODO
}

p4_pd_status_t mc_l2_node_destroy(
  p4_pd_sess_hdl_t session, int8_t device, mc_l2_node_hdl_t l2_hdl
) {
  (void) session;
  pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l2_node_destroy(l2_hdl);
  return 0; // TODO
}

p4_pd_status_t mc_l2_node_update(
  p4_pd_sess_hdl_t session, int8_t device,
  mc_l2_node_hdl_t l2_hdl, const uint8_t *port_map, const uint8_t *lag_map
) {
  (void) session; (void) lag_map;
  std::string port_map_ = convert_map(port_map, PRE_PORTS_MAX);
  pd_conn_mgr_client(conn_mgr_state, device)->bm_mc_l2_node_update(l2_hdl, port_map_);
  return 0; // TODO
}

p4_pd_status_t mc_l2_lag_update(p4_pd_sess_hdl_t session,
				int8_t dev_id,
				mgrp_lag_id_t lag_id,
				const uint8_t *port_map) {
  (void) session; (void) dev_id; (void) lag_id; (void) port_map;
  return 0;
}

}