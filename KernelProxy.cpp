namespace Kernel
{
	extern void Init();
	extern void Main();
}

extern "C"
{
	void KernelInitProxy()
	{
		Kernel::Init();
	}

	void KernelMainProxy()
	{
		Kernel::Main();
	}
}
