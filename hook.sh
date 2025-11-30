#!/bin/sh

run_latehook() {
	local conf=""

	if [ "x$ovlroot" != "x" ]; then
		if [ "$ovlroot" != "y" ]; then
			conf="$ovlroot"
		fi

		/bin/ovlroot.sh "$conf"
	fi

	return 0
}

