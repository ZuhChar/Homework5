# 
# Makefile
# Author: Zachary Crimmel
# Date: Mar 7, 2022
#
# COSC 3750, Homework 5
#
# This is a Makefile designed to compile the wyls.c file
#

CC= gcc
CFLAGS= -Wall -ggdb
RM= rm -f

.PHONY: wyls clean tidy

wyls: wyls.c
	$(CC) $(CFLAGS) wyls.c -o wyls

clean:
	${RM} wyls

tidy:
	${RM} a.out core.* wyls
