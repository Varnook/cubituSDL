extern malloc
extern free
global mulMa

section .text

; rdi = float* A[4][4]
; rsi = float* B[4][4]
mulMa:
	push rbp
	mov rbp, rsp

	push r12
	sub rsp, 8

	mov r12, rdi ; Guardo A y transpongo B
	mov rdi, rsi
	call trMa    ; rax = B, r12 = A

	mov rcx, 4
	.ciclo:
		movaps xmm1, [r12]

		mov rdi, 0
		mov rsi, 0
		.cicloInterno:
			movaps xmm2, [rax + rdi] ; xmm2 = (B[rdi], B[rdi+1], B[rdi+2], B[rdi+3])

			movaps xmm0, xmm1 ; Sobre xmm0 se van a hacer las operaciones y meter en A.
			mulps  xmm0, xmm2 ; A[i] * B[j]
			haddps xmm0, xmm0 
			haddps xmm0, xmm0 ; A[i][0] + A[i][1] + A[i][2] + A[i][3]

			movss [r12 + rsi], xmm0

			add rdi, 16
			add rsi, 4
			cmp rsi, 16
		jne .cicloInterno

		add r12, 16
	loop .ciclo

	mov rdi, rax ; Libero la matriz/vector B trnaspuesta
	call free

	add rsp, 8
	pop r12
	
	pop rbp
ret

; float* trMa(A)
; Clona la matriz con malloc, la transpone y devuelve un vector de 16 floats.
; rdi = float* A
trMa:
	push rbp
	mov rbp, rsp

	push r12
	push r13

	mov r12, rdi ; r12 = A
	
	mov rdi, 64 ; rdi = sizeof(float) * 16
	call malloc ; rax = float* 
	; todo ver bien si malloc siempre devuelve alineado a 16 bytes.

	mov rcx, 4  ; Itero por cada vector.
	mov rdi, 0
	.ciclo:
		movaps xmm0, [r12] ; Muevo a xmm0 el vector de 4 floats en r12.

			mov rsi, 0
			.cicloInterno:
				mov r13, rsi            ; Con r13 voy a moverme por
				add r13, rdi 
				movss [rax + r13], xmm0 ; Pongo lo último que hay en xmm0 en rax[rcx][rsi]
				psrldq xmm0, 4

				add rsi, 16             ; por la columna de rax.
				cmp rsi, 64
			jne .cicloInterno

		add rdi, 4
		add r12, 16       ; me muevo al siguiente vector de 4 floats.
	loop .ciclo

	pop r13
	pop r12
	pop rbp
ret
