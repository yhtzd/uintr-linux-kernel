/* SPDX-License-Identifier: GPL-2.0 */
#ifndef _ASM_X86_SKYLOFT_H
#define _ASM_X86_SKYLOFT_H

#ifdef CONFIG_X86_USER_INTERRUPTS

struct skyloft_cpu_state {
	bool skyloft_enabled; /* Is this CPU bound for skyloft? */
	u32 saved_apic_lvtt; /* Saved APIC LVT timer register */
	u32 saved_apic_tmict; /* Saved APIC Initial Count Regsiter */
	u32 saved_apic_tdcr; /* Saved APIC Divide Configuration Register */
};

DECLARE_PER_CPU(struct skyloft_cpu_state, skyloft_cpu_state);

int skyloft_enable(void);
int skyloft_disable(void);

#define is_skyloft_enabled() (this_cpu_ptr(&skyloft_cpu_state)->skyloft_enabled)
#define skyloft_lapic_mask() \
	(apic_write(APIC_LVTT, apic_read(APIC_LVTT) | APIC_LVT_MASKED))
#define skyloft_lapic_unmask() \
	(apic_write(APIC_LVTT, apic_read(APIC_LVTT) & ~APIC_LVT_MASKED))

#endif /* CONFIG_X86_USER_INTERRUPTS */

#endif /* _ASM_X86_SKYLOFT_H */
