#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "stdio.h"



#include "esp_system.h"
#include "esp_wifi.h"

#include "string.h"
// #include "portmodules.h"


esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);
uint8_t beacon_raw[] = {
	0x80, 0x00,							// 0-1: Frame Control
	0x00, 0x00,							// 2-3: Duration
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff,				// 4-9: Destination address (broadcast)
	0xba, 0xde, 0xaf, 0xfe, 0x00, 0x06,				// 10-15: Source address
	0xba, 0xde, 0xaf, 0xfe, 0x00, 0x06,				// 16-21: BSSID
	0x00, 0x00,							// 22-23: Sequence / fragment number
	0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,			// 24-31: Timestamp (GETS OVERWRITTEN TO 0 BY HARDWARE)
	0x64, 0x00,							// 32-33: Beacon interval
	0x31, 0x04,							// 34-35: Capability info
	0x00, 0x00, /* FILL CONTENT HERE */				// 36-38: SSID parameter set, 0x00:length:content
	0x01, 0x08, 0x82, 0x84,	0x8b, 0x96, 0x0c, 0x12, 0x18, 0x24,	// 39-48: Supported rates
	0x03, 0x01, 0x01,						// 49-51: DS Parameter set, current channel 1 (= 0x01),
	0x05, 0x04, 0x01, 0x02, 0x00, 0x00,				// 52-57: Traffic Indication Map
	
};

#define BEACON_SSID_OFFSET 38
#define SRCADDR_OFFSET 10
#define BSSID_OFFSET 16
#define SEQNUM_OFFSET 22
#define TOTAL_LINES (sizeof(rick_ssids) / sizeof(char *))


char *rick_ssids[] = {
	"01 Never gonna give you up",
	"02 Never gonna let you down",
	"03 Never gonna run around",
	"04 and desert you",
	"05 Never gonna make you cry",
	"06 Never gonna say goodbye",
	"07 Never gonna tell a lie",
	"08 and hurt you"
};

STATIC mp_obj_t raw_hello(void){
  printf("Heya there!\n");
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(raw_hello_obj, raw_hello);

STATIC mp_obj_t saySomething(mp_obj_t something){
  printf("You said: %s\n", mp_obj_str_get_str(something));
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(saySomething_obj, saySomething);

STATIC mp_obj_t packetTest(void){
  uint8_t line = 0;

	// Keep track of beacon sequence numbers on a per-songline-basis
	uint16_t seqnum[TOTAL_LINES] = { 0 };

	for (;;) {
		vTaskDelay(100 / TOTAL_LINES / portTICK_PERIOD_MS);

		// Insert line of Rick Astley's "Never Gonna Give You Up" into beacon packet
		printf("%i %i %s\r\n", strlen(rick_ssids[line]), TOTAL_LINES, rick_ssids[line]);

		uint8_t beacon_rick[200];
		memcpy(beacon_rick, beacon_raw, BEACON_SSID_OFFSET - 1);
		beacon_rick[BEACON_SSID_OFFSET - 1] = strlen(rick_ssids[line]);
		memcpy(&beacon_rick[BEACON_SSID_OFFSET], rick_ssids[line], strlen(rick_ssids[line]));
		memcpy(&beacon_rick[BEACON_SSID_OFFSET + strlen(rick_ssids[line])], &beacon_raw[BEACON_SSID_OFFSET], sizeof(beacon_raw) - BEACON_SSID_OFFSET);

		// Last byte of source address / BSSID will be line number - emulate multiple APs broadcasting one song line each
		beacon_rick[SRCADDR_OFFSET + 5] = line;
		beacon_rick[BSSID_OFFSET + 5] = line;

		// Update sequence number
		beacon_rick[SEQNUM_OFFSET] = (seqnum[line] & 0x0f) << 4;
		beacon_rick[SEQNUM_OFFSET + 1] = (seqnum[line] & 0xff0) >> 4;
		seqnum[line]++;
		if (seqnum[line] > 0xfff)
			seqnum[line] = 0;

		esp_wifi_80211_tx(WIFI_IF_AP, beacon_rick, sizeof(beacon_raw) + strlen(rick_ssids[line]), false);
    
    for(int i = 0; i < sizeof(beacon_raw) + strlen(rick_ssids[line]); i++){
      printf("%d: %d\n", i, beacon_rick[i]);
    }

		if (++line >= TOTAL_LINES)
			line = 0;
	}
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(packetTest_obj, packetTest);

STATIC mp_obj_t sendPacket(const mp_obj_t payload){
  mp_uint_t len;
  mp_obj_t *data;
  mp_obj_get_array(payload, &len, &data);
  for(int i = 0; i < len; i++){
    // printf("%d\n", data[i]);
    printf("%d\n", mp_obj_get_int(data[i]));
  }
  // esp_wifi_80211_tx(WIFI_IF_AP, payload, len, false);
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(sendPacket_obj, sendPacket);


// STATIC const mp_rom_map_elem_t raw_packet_rawSupported_locals_dict_table[] = {};
// STATIC MP_DEFINE_CONST_DICT(raw_packet_rawSupported, raw_packet_rawSupported_locals_dict_table);
//
// const mp_obj_type_t raw_packet_rawSupportedObj_type = {
//   {&}
// }



STATIC const mp_map_elem_t rawpacket_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_rawpacket) },
    {MP_OBJ_NEW_QSTR(MP_QSTR_hey), (mp_obj_t)&raw_hello_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_say_something), (mp_obj_t)&saySomething_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_packetTest), (mp_obj_t)&packetTest_obj},
    {MP_OBJ_NEW_QSTR(MP_QSTR_sendPacket), (mp_obj_t)&sendPacket_obj},
};

STATIC MP_DEFINE_CONST_DICT (
    mp_module_rawpacket_globals,
    rawpacket_globals_table
);

const mp_obj_module_t mp_module_rawpacket = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_rawpacket_globals,
};
