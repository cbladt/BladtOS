global _DoLoadGDT

_DoLoadGDT:
    mov eax, [esp + 8]
    lgdt [eax]
    ret
