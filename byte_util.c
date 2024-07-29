void reverse(uint8_t* p_buf, uint32_t size)
{
    int     i, j;
    uint8_t tmp;
    // 4byte 1234 -> 1uint32 4321
    for (i=0, j=size-1; i<j; i++, j--)
    {
        tmp = p_buf[i];
        p_buf[i] = p_buf[j];
        p_buf[j] = tmp;
    }
}

uint32_t swap32(uint32_t data) {
	return ((data >> 16) | (data << 16));
}
