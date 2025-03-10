/***************************************************************************************************\
*																									*
*									DIZAHEX DISASSEMBLER ENGINE										*
*																									*
*								 (characteristics and packed table)									*
*																									*
*					(��� ������������� ��������� ������� � ����� dizahex_disasm())					*
*																									*
\***************************************************************************************************/



																			//pr0mix
																			//���������� ��� ���� - ��������� �����



#ifndef DH_TBL_H
#define DH_TBL_H



#define C_NONE				0x000
#define C_PREFIX			0x001
#define C_MODRM				0x002
#define C_DATA_8			0x004
#define C_DATA_16			0x008
#define C_DATA_PFX_66_67	0x010
#define C_REL_8				0x020
#define C_REL_32			0x040

#define C_OP_EXTENDED		0x100



uint8_t dizahex_table[] = 
{
	0x80, 0x84, 0x80, 0x84, 0x80, 0x84, 0x80, 0x84,
	0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 0x80, 0x88, 
	0x8C, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 0x8B, 
	0x90, 0x94, 0x98, 0x8B, 0x9C, 0x9C, 0x9C, 0x9C,
	0xA0, 0x80, 0x80, 0x80, 0x8B, 0x8B, 0xA4, 0x8B,
	0xA8, 0x8B, 0x84, 0x8B, 0xAC, 0xAC, 0xA8, 0xA8,
	0xB0, 0xB4, 0xB8, 0xBC, 0x80, 0xC0, 0x80, 0x80,
	0x9C, 0xAC, 0xC4, 0x8B, 0xC8, 0x90, 0x8B, 0x90,
	0x80, 0x8B, 0x8B, 0xCC, 0x80, 0x80, 0x80, 0x80,
	0x80, 0xD0, 0x80, 0x80, 0x8B, 0x90, 0x8B, 0x8B,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0xD4, 0xD8, 0x80, 0x80,
	0xDC, 0xDC, 0xDC, 0xDC, 0x80, 0x80, 0x80, 0x80,
	0x8F, 0xD7, 0x8F, 0xD7, 0x80, 0x80, 0xE0, 0x80,
	0xE4, 0xD5, 0x8B, 0x8B, 0x80, 0x80, 0x80, 0x80,
	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xD8,

	0x02, 0x02, 0x02, 0x02, 0x04, 0x10, 0x00, 0x00,
	0x04, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01,
	0x10, 0x12, 0x04, 0x06, 0x24, 0x24, 0x24, 0x24,
	0x06, 0x12, 0x06, 0x06, 0x00, 0x00, 0x18, 0x00, 
	0x10, 0x10, 0x10, 0x10, 0x04, 0x04, 0x04, 0x04,
	0x06, 0x06, 0x08, 0x00, 0x02, 0x02, 0x06, 0x12,
	0x0C, 0x00, 0x08, 0x00, 0x00, 0x04, 0x00, 0x00,
	0x04, 0x04, 0x00, 0x00, 0x50, 0x50, 0x18, 0x24,
	0x01, 0x00, 0x01, 0x01, 0x00, 0x02, 0x00, 0x06,
	0x02, 0x00, 0x02, 0x00, 0x06, 0x06, 0x06, 0x06, 
	0x02, 0x02, 0x02, 0x00, 0x50, 0x50, 0x50, 0x50, 
	0x50, 0x00, 0x06, 0x02, 0x02, 0x02, 0x06, 0x02
};



#endif /* DH_TBL_H */
