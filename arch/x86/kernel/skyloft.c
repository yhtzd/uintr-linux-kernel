#include <linux/percpu-defs.h>

#include <asm/apic.h>
#include <asm/skyloft.h>
#include <asm/irq_vectors.h>

DEFINE_PER_CPU(struct skyloft_cpu_state, skyloft_cpu_state);
EXPORT_SYMBOL(skyloft_cpu_state);

int skyloft_enable(void)
{
	unsigned long flags;
	struct skyloft_cpu_state *state;

	local_irq_save(flags);
	state = this_cpu_ptr(&skyloft_cpu_state);
	if (state->skyloft_enabled) {
		local_irq_restore(flags);
		return -EEXIST;
	}

	state->saved_apic_lvtt = apic_read(APIC_LVTT);
	state->saved_apic_tdcr = apic_read(APIC_TDCR);
	state->saved_apic_tmict = apic_read(APIC_TMICT);
	state->skyloft_enabled = true;
	apic_write(APIC_LVTT, APIC_LVT_MASKED | APIC_LVT_TIMER_PERIODIC |
				      UINTR_SKYLOFT_VECTOR);

	local_irq_restore(flags);
	return 0;
}
EXPORT_SYMBOL(skyloft_enable);

int skyloft_disable(void)
{
	unsigned long flags;
	struct skyloft_cpu_state *state;

	local_irq_save(flags);
	state = this_cpu_ptr(&skyloft_cpu_state);
	if (!state->skyloft_enabled) {
		local_irq_restore(flags);
		return -EINVAL;
	}

	apic_write(APIC_LVTT, state->saved_apic_lvtt);
	apic_write(APIC_TDCR, state->saved_apic_tdcr);
	apic_write(APIC_TMICT, state->saved_apic_tmict);
	state->skyloft_enabled = false;

	local_irq_restore(flags);
	return 0;
}
EXPORT_SYMBOL(skyloft_disable);
