ani_backlightctl:
	gcc ani_backlightctl.c -o ani_backlightctl

install: ani_backlightctl
	sudo mv ani_backlightctl /usr/bin
