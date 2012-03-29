#ifndef _SIMICS_MAGIC_INSTRUCTION_H
#define _SIMICS_MAGIC_INSTRUCTION_H

/*
 * This file contains the magic instructions for different target
  * architectures, as understood by different compilers.
   *
    *   arch   instr           limit               compilers
	 *   -----------------------------------------------------
	  *   ia64   nop 0x1?????    0 <= n < 0x100000   gcc
	   *   mips   li $zero,n      0 <= n <= 0xffff    gcc
	    *   msp430 bis r0,r0       n == 0              gcc
		 *   ppc    mr n,n          0 <= n < 32         gcc
		  *   ppc64  fmr n,n         0 <= n < 32         gcc
		   *   sparc  sethi n,%g0     0 <  n < (1 << 22)  gcc, WS C[++]
		    *   x86    xchg bx,bx      n == 0              gcc
			 * 
			  */



			  /* BEGIN EXPORT simics/magic-instruction.h */

#define __MAGIC_CASSERT(p) do {                                 \
        typedef int __check_magic_argument[(p) ? 1 : -1];       \
} while (0)

#if defined(__GNUC__) || defined(__INTEL_COMPILER)
#if defined(__sparc) || defined(__sparc__)

#define MAGIC(n) do {                                   \
        __MAGIC_CASSERT((n) > 0 && (n) < (1U << 22));   \
		        __asm__ __volatile__ ("sethi " #n ", %g0");     \
} while (0)

#define MAGIC_BREAKPOINT MAGIC(0x40000)



#else  /* !__sparc && !__i386 && !__powerpc__ */
#error "Unsupported architecture"
#endif /* !__sparc && !__i386 && !__powerpc__ */

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#if defined(__sparc)

#define MAGIC(n) do {                                   \
        __MAGIC_CASSERT((n) > 0 && (n) < (1U << 22));   \
		        asm ("sethi " #n ", %g0");                      \
} while (0)

#define MAGIC_BREAKPOINT MAGIC(0x40000)

#else  /* !__sparc */
#error "Unsupported architecture"
#endif /* !__sparc */

#elif defined(__DECC)

#else  /* !__GNUC__ && !__SUNPRO_C && !__SUNPRO_CC && !__DECC */

#ifdef _MSC_VER
#define MAGIC(n)
#define MAGIC_BREAKPOINT
#pragma message("MAGIC() macro needs attention!")
#else
#error "Unsupported compiler"
#endif

#endif /* !__GNUC__ && !__SUNPRO_C && !__SUNPRO_CC && !__DECC  */

#endif /* _SIMICS_MAGIC_INSTRUCTION_H */

