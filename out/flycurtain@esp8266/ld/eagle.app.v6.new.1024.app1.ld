MEMORY
{
  dport0_0_seg (rw) : org = 0x3FF00000, len = 0x10
  dram0_0_seg (rw) : org = 0x3FFE8000, len = 0x18000
  iram1_0_seg (rx) : org = 0x40100000, len = 0x8000
  irom0_0_seg (rx) : org = 0x40201010, len = 0xE0000
}
INCLUDE "../ld/eagle.app.v6.common.ld"
_heap_size = 0x40000000 - _heap_start;
