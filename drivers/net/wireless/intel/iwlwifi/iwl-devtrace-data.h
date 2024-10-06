/* SPDX-License-Identifier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2009 - 2014 Intel Corporation. All rights reserved.
 * Copyright(c) 2015        Intel Deutschland GmbH
 * Copyright(c) 2018 - 2019, 2023-2024 Intel Corporation
 *****************************************************************************/

#if !defined(__IWLWIFI_DEVICE_TRACE_DATA) || defined(TRACE_HEADER_MULTI_READ)
#define __IWLWIFI_DEVICE_TRACE_DATA

#include <linux/tracepoint.h>

#undef TRACE_SYSTEM
#define TRACE_SYSTEM iwlwifi_data

TRACE_EVENT(iwlwifi_dev_tx_tb,
	TP_PROTO(const struct device *dev, struct sk_buff *skb,
		 u8 *data_src, dma_addr_t phys, size_t data_len),
	TP_ARGS(dev, skb, data_src, phys, data_len),
	TP_STRUCT__entry(
		DEV_ENTRY
		__field(u64, phys)

		__dynamic_array(u8, data,
				iwl_trace_data(skb) ? data_len : 0)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		__entry->phys = phys;
		if (__get_dynamic_array_len(data))
			memcpy(__get_dynamic_array(data), data_src, data_len);
	),
	TP_printk("[%s] TX frame data", __get_str(dev))
);

TRACE_EVENT(iwlwifi_dev_rx_data,
	TP_PROTO(const struct device *dev,
		 void *rxbuf, size_t len, size_t start),
	TP_ARGS(dev, rxbuf, len, start),
	TP_STRUCT__entry(
		DEV_ENTRY
		__dynamic_array(u8, data, len - start)
	),
	TP_fast_assign(
		DEV_ASSIGN;
		if (start < len)
			memcpy(__get_dynamic_array(data),
			       ((u8 *)rxbuf) + start, len - start);
	),
	TP_printk("[%s] RX frame data", __get_str(dev))
);
#endif /* __IWLWIFI_DEVICE_TRACE_DATA */

#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH .
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_FILE iwl-devtrace-data
#include <trace/define_trace.h>
