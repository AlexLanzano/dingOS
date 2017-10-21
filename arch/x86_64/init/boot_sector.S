boot_sector:
OEM:					.ascii "DingOS"
sector_size:			.word 0x200
cluster_size:			.byte 1
reserved_sectors:		.word 1
FAT_copies:       		.byte  2
root_size:     			.word  224
total_sectors:    		.word  2880
media_descriptor:		.byte  0xF0
FAT_size:      			.word  9
track_size:    			.word  9
head_count:      		.word  2
hidden_sectors:   		.int   0
sector32:       		.int   0
boot_drive:    			.byte  0
reserved:     			.byte  0
boot_signature:     	.byte  0x29
disk_serial:        	.ascii "seri"
volume_lable: 			.ascii "MYVOLUME   "
fs_type:      			.ascii "FAT16   "
