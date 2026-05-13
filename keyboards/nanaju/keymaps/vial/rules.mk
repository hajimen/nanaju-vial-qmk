SRC += qa_test.c

ifeq ($(strip $(NANAJU)), kvm)
	OPT_DEFS += -DPRODUCT=\"DecentKeyboards\ Nanaju\ KVM\ rev\ $(REV)\"
endif
ifeq ($(strip $(NANAJU)), full)
	VIA_ENABLE = yes
	VIAL_ENABLE = yes
	QMK_SETTINGS = yes
	MOUSEKEY_ENABLE = yes
	NKRO_ENABLE = yes
	JOYSTICK_ENABLE = yes
	JOYSTICK_DRIVER = digital
	COMBO_ENABLE = yes
	KEY_OVERRIDE_ENABLE = yes
	REPEAT_KEY_ENABLE = yes
	OPT_DEFS += -DPRODUCT=\"DecentKeyboards\ Nanaju\ rev\ $(REV)\"
endif
ifeq ($(strip $(NANAJU)), test_fixture)
	OPT_DEFS += -DPRODUCT=\"DecentKeyboards\ Nanaju\ Test\ Fixture\ rev\ $(REV)\"
	OPT_DEFS += -DTEST_FIXTURE
endif

EXTRAKEY_ENABLE = yes
BOOTMAGIC_ENABLE = yes
TAP_DANCE_ENABLE = yes
CONSOLE_ENABLE = no
