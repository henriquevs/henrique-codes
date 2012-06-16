@Aluno1:095725:Francine Domingos de Paula
@Aluno2:105063:Henrique Vicente Souza

@**********************************************************************************
@ Instituto de Computacao da UNICAMP
@ Disciplina MC404E: Primeiro Semestre de 2012
@ Laboratorio 09: Conta(ARM)
@ Autores: Francine Domingos de Paula RA:095725
@          Henrique Vicente Souza     RA:105063	
@**********************************************************************************	

.org 0x1000
@ Tabela de Digitos: Vetor de conversao decimal/ display de 7 segmentos
.data 
TABDIG: .byte 0x7e, 0x30, 0x6d, 0x79, 0x33, 0x5b, 0x5f, 0x70, 0x7f, 0x7b
.equ READY, 0x1

main:

	@ zera contadores para uso
	mov r3, #0x0
	mov r4, #0x0
	mov r5, #0x0
	mov r6, #0x0

	@ carrega todos as portas
	mov r7, #0x90000
	mov r8, #0x0110		@Liga
	orr r8, r7
	
	mov r9, #0x0120		@Conta
	orr r9, r7
	
	mov r10, #0x0130	@LED
	orr r10, r7
	
	mov r11, #0x0140	@Display1
	orr r11, r7

	mov r12, #0x0150	@Display2
	orr r12, r7

	mov r13, #0x0160	@Display3
	orr r13, r7

	mov r14, #0x0170	@Display4
	orr r14, r7
	
	
	mov r0, #0x7e
	strb r0, [r11] 		@Escreve no display 0
	strb r0, [r12]	
	strb r0, [r13]
	strb r0, [r14]
		
zera:

	@ Desativa a acao do botao Conta
	mov r0, #0
	strb r0, [r8]

loop:

	@ Fica continuamente num loop verificando se botão LIGA foi pressionado
	ldr r2, [r8]
	
	@ Usa "LIGA" como flag para setar o LED
	strb r2, [r10]

	ldr r0, [r9]
	cmp r0, #READY			@ Clicou em contar?
	bne loop			@ Se nao clicou, volta pro loop
	b seta				@ Se clicou, aumenta a contagem

limpa:
	b main

seta:
	
	cmp r2, #READY			@ Esta ligado?
	bne zera			@ Se nao estiver, zera botao de contagem

	@mov r3, #0x0
	cmp r3, #9			@ Chegou na unidade 9?
	beq addDez			@ Se sim, aumenta dezena

	add r3, #1			@ Adiciona 1 na unidade
	b atualizaUnidade

addDez:
	mov r3, #0x0			@ Zera a unidade
	cmp r4, #9			@ Chegou na dezena 9?
	beq addCent			@ Se sim, aumenta centena
	add r4, #1			@ Se não, aumenta 1 na dezena
	b atualizaDez

addCent:

	mov r4, #0x0			@ Zera a dezena
	cmp r5, #9			@ Chegou na centena 9?
	beq addMil			@ Se sim, aumenta no mil
	add r5, #1			@ Se não, aumenta 1 na centena
	b atualizaCent

addMil:
	mov r5, #0x0			@ Zera a centena
	cmp r6, #9			@ Chegou em 9999?
	beq limpa			@ Se sim, zera o display e recomeça
	mov r6, #1			@ Se não, aumenta 1 em mil

atualizaMil:

	mov r1, #TABDIG			@  Prepara para determinar codificação do digito lido *
	ldr r1, [r1, r6]		@ Carrega a codificação correspondente **
	strb r1, [r11]			@ Escreve no mostrador ***

atualizaCent:

	mov r1, #TABDIG			@ *
	ldr r1, [r1, r5]		@ **
	strb r1, [r12]			@ ***

atualizaDez:

	mov r1, #TABDIG			@ *
	ldr r1, [r1, r4]		@ **
	strb r1, [r13]			@ ***

atualizaUnidade:

	mov r1, #TABDIG			@ *
	ldr r1, [r1,r3]			@ **
	strb r1, [r14]			@ ***

	b loop				@ Continua verificando





	