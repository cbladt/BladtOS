char *fb;

void write(unsigned short i, char c)
{
    fb[i] = c;
    fb[i + 1] = ((0 & 0x0F) << 4) | (15 & 0x0F);
}

void kmain()
{    
    fb = (char *) 0x000B8000;

    //char* txt = "BLADT";

    for (int n = 0; n < 5; n += 2)
    {
	write(n, 'A');
    }
}
