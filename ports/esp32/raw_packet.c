#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "stdio.h"
// #include "portmodules.h"

STATIC mp_obj_t raw_hello(void){
  printf("Heya there!\n");
  return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(raw_hello_obj, raw_hello);

STATIC const mp_map_elem_t rawpacket_globals_table[] = {
    { MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_rawpacket) },
    {MP_OBJ_NEW_QSTR(MP_QSTR_hey), (mp_obj_t)&raw_hello_obj},
};

STATIC MP_DEFINE_CONST_DICT (
    mp_module_rawpacket_globals,
    rawpacket_globals_table
);

const mp_obj_module_t mp_module_rawpacket = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_rawpacket_globals,
};
