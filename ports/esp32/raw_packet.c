// #include "py/nlr.h"
// #include "py/obj.h"
// #include "py/runtime.h"
// #include "py/binary.h"
// // #include "portmodules.h"
//
//
// #include "netutils.h"
// #include "esp_wifi.h"
// #include "esp_wifi_types.h"
//
// STATIC const mp_map_elem_t rawpacket_globals_table[] = {
//     { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_rawpacket) },
// };
//
// STATIC MP_DEFINE_CONST_DICT(mp_module_rawpacket_globals,
//     rawpacket_globals_table);
//
// // const mp_obj_type_t rawpacket_type = {
// //     { &mp_type_type },
// //     .name = MP_QSTR_rawpacket,
// //     .locals_dict = (mp_obj_t)&rawpacket_locals_dict,
// // };
//
// // STATIC const mp_rom_map_elem_t mp_module_rawpacket_globals_table[] = {
// //     { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_rawpacket) },
//
//     // { MP_ROM_QSTR(MP_QSTR_localtime), MP_ROM_PTR(&time_localtime_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_mktime), MP_ROM_PTR(&time_mktime_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_time), MP_ROM_PTR(&time_time_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_sleep), MP_ROM_PTR(&mp_utime_sleep_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_sleep_ms), MP_ROM_PTR(&mp_utime_sleep_ms_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_sleep_us), MP_ROM_PTR(&mp_utime_sleep_us_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_ticks_ms), MP_ROM_PTR(&mp_utime_ticks_ms_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_ticks_us), MP_ROM_PTR(&mp_utime_ticks_us_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_ticks_cpu), MP_ROM_PTR(&mp_utime_ticks_cpu_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_ticks_add), MP_ROM_PTR(&mp_utime_ticks_add_obj) },
//     // { MP_ROM_QSTR(MP_QSTR_ticks_diff), MP_ROM_PTR(&mp_utime_ticks_diff_obj) },
// // };
//
// // STATIC MP_DEFINE_CONST_DICT(mp_module_rawpacket_globals, mp_module_rawpacket_globals_table);
//
// const mp_obj_module_t mp_module_rawpacket = {
//     .base = { &mp_type_module },
//     .globals = (mp_obj_dict_t*)&mp_module_rawpacket_globals,
// };


#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
// #include "portmodules.h"

STATIC const mp_map_elem_t rawpacket_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_rawpacket) },
};

STATIC MP_DEFINE_CONST_DICT (
    mp_module_rawpacket_globals,
    rawpacket_globals_table
);

const mp_obj_module_t mp_module_rawpacket = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_rawpacket_globals,
};
