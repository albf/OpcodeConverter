/***************************************************************************
 *   Copyright (C) 2015 by                                                 *
 *   - Carlos Eduardo Millani (carloseduardomillani@gmail.com)             *
 *   - Edson Borin (edson@ic.unicamp.br)                                   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
    
#ifndef VM_H
#define VM_H

#include "config.h"
#include <inttypes.h>

#define VM_MEMORY_SZ PROCESSOR_MEMORY_SZ /* Available memory from the microprocessor  */
#define VM_MEMORY_SZDIVR4 1280 
/* Register file. */
extern uint32_t RF[32];
/*VM memory vector*/
extern uint8_t VM_memory[VM_MEMORY_SZ];
extern uint32_t VM_memory2[VM_MEMORY_SZDIVR4];

uint32_t fetch(uint32_t PC);
void vm_cpu_count(uint32_t newPC);
void vm_cpu(uint32_t newPC, int opt);
void vm_cpu_2(uint32_t newPC, int opt);
void vm_cpu_2_indirect(uint32_t newPC,int opt);
void vm_cpu_identify_instructions(uint32_t newPC);
void vm_cpu_init_only(uint32_t newPC, int opt);
void vm_cpu_super(uint32_t newPC, int opt);
void advance_pc(int32_t offset);

void vm_cpu_4(uint32_t newPC,int opt, int size);
void vm_cpu_2_mem2(uint32_t newPC,int opt, int i );

void vm_cpu_2_mem2_all(uint32_t newPC,int opt);
void vm_cpu_2_mem2_all_opt4(uint32_t newPC,int opt);
void vm_cpu_2_indirect_pure(uint32_t newPC,int opt);
void vm_cpu_2_indirect_pure_opt3(uint32_t newPC,int opt);
void vm_cpu_2_indirect_pure_opt4(uint32_t newPC,int opt);

void vm_cpu_2_pure_with_convertion(uint32_t newPC,int opt);
void vm_cpu_super_3(uint32_t newPC, int opt);


void print_memory(void);
void print_registers(void);

#endif // VM_H

#ifdef __cplusplus
}
#endif