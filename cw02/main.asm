/*
 * Autor: pidpawel
 * Temat: dodawanie wielobajtowych liczb
 * 
 * Rozmiar liczb określany w stałej LEN
 * Wynik w tablicy tab_2
 */

 #include "m32def.inc"

 .EQU LEN = 16


 .DSEG
 tab_1: .BYTE LEN
 tab_2: .BYTE LEN


 .CSEG
 .ORG 0


START:
	LDI ZL, low(LEN)  ; W Z trzymam licznik pozostałych bajtów do końca obliczeń
	LDI ZH, high(LEN)

	LDI XL, low(tab_1)  ; W X trzymam adres aktualnie obrabianego bajtu tab_1
	LDI XH, high(tab_1)

	LDI YL, low(tab_2)  ; W Y trzymam adres aktualnie obrabianego bajtu tab_2
	LDI YH, high(tab_2)

	ADD XL, ZL  ; Przechodzę na końce tablic, dobre miejsce na breakpoint (widać gdzie zaczynająsię tab_1 i tab_2)
	ADC XH, ZH

	ADD YL, ZL
	ADC YH, ZH

	LDI R19, 0  ; W R19 trzymam informację czy było przeniesienie w ostatnim przejściu pętli
	LDI R20, 0  ; Pomocnicze "0" do porównań


LOOP:
	LD R16, -X  ; Ładuję obrabiane bajty
	LD R17, -Y

	CPI R19, 0  ; Czytam zapisany stan przeniesienia
	BREQ CLEARC
	BRNE SETC
AFTERRESTORE:

	ADC R17, R16  ; Właściwe dodawanie

	BRCS REMEMBERC  ; Zapisuję stan przeniesienia
	BRCC REMEMBERNC
AFTERREMEMBER:

	ST Y, R17  ; Wracam z wynikiem do Y

	SBIW ZL, 1  ; Dekrementuję Z

	CP R20, ZL  ; Jako że to dwubajtowa zmienna to porównuję na 2 razy
	CPC R20, ZH
	BREQ PRE_FINISH
	
	JMP LOOP


; Odtwarzanie stanu przeniesienia
SETC:
	SEC
	JMP AFTERRESTORE

CLEARC:
	CLC
	JMP AFTERRESTORE


; Zapisywanie stanu przeniesienia
REMEMBERC:
	LDI R19, 1
	JMP AFTERREMEMBER

REMEMBERNC:
	LDI R19, 0
	JMP AFTERREMEMBER


; Przywracam flagę przeniesienia po zakończeniu dodawania
PRE_FINISH:
	CPI R19, 0  ; Czytam zapisany stan przeniesienia
	BREQ PRE_FINISH_CLRC
	BRNE PRE_FINISH_SETC

PRE_FINISH_SETC:
	SEC
	JMP STOP

PRE_FINISH_CLRC:
	CLC
	JMP STOP


; Halt and Catch Fire :)
STOP:
	JMP STOP  ; Drugie dobre miejsce na breakpoint
