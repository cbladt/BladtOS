global OutByte
global InByte

OutByte:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

InByte:
    mov dx, [esp + 4]
    in al, dx
    ret
