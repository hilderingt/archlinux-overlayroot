# archlinux-overlayroot
With _overlayroot_ you can overlay your root filesystem with a temporary tmpfs
filesystem to mount it read-only afterwards. Any changes are written to the
tmpfs filesystem (which resides in memory), so that these changes are discarded
on reboot or a loss of power does not threaten the integrity of the system's 
root filesystem. Additionally you can configure further filesystems that you
want either overlayed by a tmpfs filesystem, too or mounted read-only because
write access is not needed and you want to protect it against changes.

## 1. Installation

### 1.1 Building Package
- change your current working directory to the directory containing the files
  of the repository
- run `makepkg`

### 1.2 Install Package
- build or download package
- run `pacman -U /<path>/<to>/archlinux-overlayroot-<version>-any.pkg.tar.zst`

## 2. Configuration

### 2.1 Initramfs
- add `overlay` to __MODULES__ array in mkinitcpio.conf (in case support for
  OverlayFS is not statically compiled into your kernel)
- add `ovlroot` to the end of __HOOKS__ array in mkinitcpio.conf
- update initramfs with `mkinitcpio -P`

### 2.2 Kernel Command Line
- add `ovlroot` to your kernel command line
- optional:
	- add the name of your configuration file like this `ovlroot=<config>`

### 2.3 Configuration File
- directory for configuration files is `/etc/ovlroot.d`
- to apply changes to configuration files run `mkinitcpio -P`
- configuration files can contain the following options:
	- `OVLROOT_INIT_ROOTMNT=/<path>/<to>/<rootfs>`
		- absolute path of the first mountpoint of the root filesystem during 
		  initramfs stage
		- default value: `/new_root`
	- `OVLROOT_BASE_TYPE=<fstype>`
		- type of underlying base filesystem
		- either `tmpfs` or an other filesystem, e. g. block-based like `ext4`
		- default value: `tmpfs`
    - `OVLROOT_BASE_OPTS=<opt>,...`
		- options to add to the mount of the underlying base filesystem
	- `OVLROOT_BASE_DEV=<dev>`
		- source device for underlying filesystem, e. g. `tmpfs` or a block device
		- default value: `tmpfs`
	- `OVLROOT_BASE_DIR=/<path>/<to>/<mountpoint>`
		- absolute path of the mountpoint for underlying base filesystem
		- default value: `/.ovlroot`
	- `OVLROOT_BASE_CLEAN=<value>`
		- when base filesystem is for example a block device, any remaining data
		  is erased when value is `y`, any other value disables this option
		- default value: `n`
	- `OVLROOT_LOWER_DIR=<dirname>`
		- relative path of the subdirectory of all lower filesystem mounts
		- default value: `lowerdir`
	- `OVLROOT_UPPER_DIR=<dirname>`
		- relative path of the subdirectory for all changes made to the filesystems
		- default value: `upperdir`
	- `OVLROOT_WORK_DIR=<dirname>`
		- relative path of the subdirectory needed by OverlayFS
		- default value: `workdir`
	- `OVLROOT_FSTAB=/<path>/<to>/<fstab>`
		- absolute path to system's fstab
		- default value: `/etc/fstab`
	- `OVLROOT_NEW_FSTAB=/<path>/<to>/<fstab>`
		- absolute path where new fstab is created temporarily
		- default value: file returned by `mktemp`
	- `OVLROOT_LOWER_MODE=<mode>`
		- lower mounts are either `rw` (read-write) or `ro` (read-only)
		- default value: `ro`
	- `OVLROOT_OVL_OPTS_ROOT=<opt>,...`
		- options added to the mount options of the root overlay mount
	- `OVLROOT_OVL_OPTS_OTHER=<opt>,...`
		- options added to the mount options of the overlay mounts given
		  in `OVLROOT_OVERLAY`
	- `OVLROOT_ROOT_FSTAB_OPTS=<value>`
		- root filesystem is remounted with options listed in system's fstab
		- ether `y` for `yes` or any other value for `no`
		- default value: `n`
	- `OVLROOT_ABORT_RO_ON_ERROR=<value>`
		- stops (`y`) or continues (any other value) rollback of changes made by
		  the script in case of error
	- `OVLROOT_LIST_SEP=<separator>`
		- character to separate list elements in `OVLROOT_OVERLAY`,`OVLROOT_RDONLY`
		  and `OVLROOT_DISABLE`
		- default value: `,`
	- `OVLROOT_OVERLAY=<mountpoint>,...`
		- list of mountpoints for which further overlay mounts are created
	- `OVLROOT_RDONLY=<mountpoint>,...`
		- list of mountpoints that are mounted read-only
    - `OVLROOT_DISABLE=<mountpoint>,...`
		- list of mountpoints that are disabled
	- `OVLROOT_SWAP=<value>`
		- disables (`off`) or enables (any other value) swap
		- default value: `on`
	- `OVLROOT_ASK_DISABLE=<value>`
		- with this option it is asked at boot time if you want to disable
		  overlayroot
		- valid values are `local`, `fifo` or `local+fifo`
		- option `local` simply reads from stdin
		- `fifo` makes the script read from a fifo, for scenarios where you
		  have ssh access during initramfs stage
		- you can simply write to the `fifo` and disable overlayroot 
		- deactivated by default
	- `OVLROOT_ASK_DISABLE_DEFAULT=<value>`
		- default value if nothing is typed in at prompt for disabling overlayroot
		- value should be `y` or `n`, but every other value than `y` is also treated
		  as `n`
		- default value: `n`
	- `OVLROOT_ASK_DISABLE_TO=<timeout>`
		- timeout in seconds for waiting for input by the user when asking for
		  disabling overlayroot
		- `-1` lets overlayroot wait indefinitely
		- default value: `15`
