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

#### 1.2 Install Package
- build or download package
- run `pacman -U /<path>/<to>/overlayroot-<version>-any.pkg.tar.zst`


## 2. Configuration

### 2.1 Initramfs
- add `overlay` to __MODULES__ array in mkinitcpio.conf (in case support for OverlayFS
  is not statically compiled into your kernel)
- add `overlayroot` to the end of __HOOKS__ array in mkinitcpio.conf
- update initramfs with `mkinitcpio -P`

### 2.2 Kernel command line
- add `overlayroot` to your kernel command line
- optional:
	- add `opts=<option>,...`
\	\	- only available option at this moment to disable swap space is `noswap`
	- add `tmpfs=/<path>/<to>/<mountpoint>,...` to `overlayroot=...` to overlay
	  filesystems with a tmpfs filesystem
	- add `ro=/<path>/<to>/<mountpoint>,...` to `overlayroot=...` to mount
	  filesystems read-only
	- specify `all` instead of dedicated mountpoints for `tmpfs` or `ro`
	- separate options with a `:`
	- examples: 
\	\	- `overlayroot=tmpfs=/usr:ro=/boot,/boot/efi`
\	\	- `overlayroot=tmpfs=all:opts=noswap`
\	\	- `overlayroot=ro=all`
