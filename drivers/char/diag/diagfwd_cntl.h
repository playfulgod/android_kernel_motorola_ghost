/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef DIAGFWD_CNTL_H
#define DIAGFWD_CNTL_H

/* Message registration commands */
#define DIAG_CTRL_MSG_REG		1
/* Message passing for DTR events */
#define DIAG_CTRL_MSG_DTR		2
/* Control Diag sleep vote, buffering etc */
#define DIAG_CTRL_MSG_DIAGMODE		3
/* Diag data based on "light" diag mask */
#define DIAG_CTRL_MSG_DIAGDATA		4
/* Send diag internal feature mask 'diag_int_feature_mask' */
#define DIAG_CTRL_MSG_FEATURE		8
/* Send Diag log mask for a particular equip id */
#define DIAG_CTRL_MSG_EQUIP_LOG_MASK	9
/* Send Diag event mask */
#define DIAG_CTRL_MSG_EVENT_MASK_V2	10
/* Send Diag F3 mask */
#define DIAG_CTRL_MSG_F3_MASK_V2	11

/* custom diag mode command to send optimized logging parameters to BP */
#define DIAG_CTRL_MSG_DIAGMODE_MDLOG 100

/* custom diag mode command to flush BP buffer */
#define DIAG_CTRL_MSG_DIAG_FLUSH     101

/* user selection, indicating whether to use optimized logging */
extern unsigned int optimized_logging;

struct cmd_code_range {
	uint16_t cmd_code_lo;
	uint16_t cmd_code_hi;
	uint32_t data;
};

struct diag_ctrl_msg {
	uint32_t version;
	uint16_t cmd_code;
	uint16_t subsysid;
	uint16_t count_entries;
	uint16_t port;
};

struct diag_ctrl_event_mask {
	uint32_t cmd_type;
	uint32_t data_len;
	uint8_t stream_id;
	uint8_t status;
	uint8_t event_config;
	uint32_t event_mask_size;
	/* Copy event mask here */
} __packed;

struct diag_ctrl_log_mask {
	uint32_t cmd_type;
	uint32_t data_len;
	uint8_t stream_id;
	uint8_t status;
	uint8_t equip_id;
	uint32_t num_items; /* Last log code for this equip_id */
	uint32_t log_mask_size; /* Size of log mask stored in log_mask[] */
	/* Copy log mask here */
} __packed;

struct diag_ctrl_msg_mask {
	uint32_t cmd_type;
	uint32_t data_len;
	uint8_t stream_id;
	uint8_t status;
	uint8_t msg_mode;
	uint16_t ssid_first; /* Start of range of supported SSIDs */
	uint16_t ssid_last; /* Last SSID in range */
	uint32_t msg_mask_size; /* ssid_last - ssid_first + 1 */
	/* Copy msg mask here */
} __packed;


struct diag_ctrl_msg_diagmode_mdlog {
	uint32_t ctrl_pkt_id;
	uint32_t ctrl_pkt_data_len;
	uint32_t version;
	uint32_t optimized;
	uint32_t commit_threshold;
	uint32_t drain_timer_val;
	uint32_t event_stale_timer_val;
	uint32_t drain_low_threshold;
	uint32_t drain_high_threshold;
	uint32_t drain_interval_in_secs;
} __packed;

struct diag_ctrl_msg_diag_flush {
	uint32_t ctrl_pkt_id;
	uint32_t ctrl_pkt_data_len;
} __packed;

struct diag_ctrl_feature_mask {
	uint32_t ctrl_pkt_id;
	uint32_t ctrl_pkt_data_len;
	uint32_t feature_mask_len;
	/* Copy feature mask here */
} __packed;

struct diag_ctrl_msg_diagmode {
	uint32_t ctrl_pkt_id;
	uint32_t ctrl_pkt_data_len;
	uint32_t version;
	uint32_t sleep_vote;
	uint32_t real_time;
	uint32_t use_nrt_values;
	uint32_t commit_threshold;
	uint32_t sleep_threshold;
	uint32_t sleep_time;
	uint32_t drain_timer_val;
	uint32_t event_stale_timer_val;
} __packed;

void diagfwd_cntl_init(void);
void diagfwd_cntl_exit(void);
void diag_read_smd_cntl_work_fn(struct work_struct *);
void diag_clean_reg_fn(struct work_struct *work);
int diag_process_smd_cntl_read_data(struct diag_smd_info *smd_info, void *buf,
								int total_recd);
void diag_send_diag_mode_update(int real_time);
void diag_send_diag_mode_update_by_smd(struct diag_smd_info *smd_info,
					int real_time);

void diag_send_diag_flush(struct diag_smd_info *smd_info);
#endif
