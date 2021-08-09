#include "YN.H"
#include "..\drivers\gcs.h"
#include "test.h"
#include <iostream.h>
#include "..\dynamics\quadrotor.h"
#include <vector>
#include "drivers\sbus.h"
#include "sbus.h"
#include "..\Mavlink\common\mavlink.h"
#include "..\Mavlink\mavlink_helpers.h"
#include <string.h>
#include <cstring>
void mavlink_send_uart_bytes(mavlink_channel_t chan, const uint8_t *ch, int length)
{
    /*unsigned char buf[255];
    unsigned char idx,index_max;
    index_max = ch.size();
    for(idx=0;i<index_max;i++)
        buf[i]=(uint8_t)ch[i];*/
    FComOut_mavlink(FCOM8, ch, length);
}
mavlink_heartbeat_t packet_in ={
	963497464,17,84,151,218,3
};
mavlink_heartbeat_t packet1;

void mavlink_test(void)
{
	std::memset(&packet1,0,sizeof(packet1));
	packet1.custom_mode = packet_in.custom_mode;
	packet1.type = packet_in.type;
	packet1.autopilot = packet_in.autopilot;
	packet1.base_mode = packet_in.base_mode;
	packet1.system_status = packet_in.system_status;
	packet1.mavlink_version = packet_in.mavlink_version;
	mavlink_msg_heartbeat_send(MAVLINK_COMM_1 , packet1.type , packet1.autopilot , packet1.base_mode , packet1.custom_mode , packet1.system_status );
}