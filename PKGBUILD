# Copyright 2025 Tim Hildering

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Maintainer: Tim Hildering <hilderingt@posteo.net>

pkgname=archlinux-overlayroot
pkgver=0.9.1
pkgrel=2
pkgdesc="Overlay the root filesystem with a tmpfs filesystem."
arch=('any')
url="https://github.com/hilderingt/archlinux-overlayroot"
license=('GPLv3')
depends=(
  'mkinitcpio'
)
makedepends=(
  'gcc'
)
source=(
  'install.sh'
  'hook.sh'
  'mount.ovlroot'
  'ovlroot.sh'
  'ovlroot-helper.c'
)
sha256sums=(
  '8be2e6680c096abb6e5d1444fb27959d7ecac59df4b5828faa121101295cff18'
  'dca9056eb5e460ee6465de921a4b77524ebc7e6a83b964c629be525934910ef0'
  'c6e15e20c35897e653d80a5ce6b3b78700d8ff35052803401bb9b2c214c45bfc'
  'fffb49dff7063d788faf935d0176a8e6a156d9b2adf1dfc0912a3d0608f3f59e'
  '1be245b8ae6618c422a7d8b5b64bb0b8061e2f1138894a6ab6f9661492b5caf0'
)

build() {
  gcc -o ovlroot-helper "$srcdir/ovlroot-helper.c"
}

package() {
  install -D -m 644 "$srcdir/install.sh" "$pkgdir/usr/lib/initcpio/install/ovlroot"
  install -D -m 644 "$srcdir/hook.sh" "$pkgdir/usr/lib/initcpio/hooks/ovlroot"
  install -D -m 755 "$srcdir/mount.ovlroot" "$pkgdir/usr/bin/mount.ovlroot"
  mkdir -p "$pkgdir/usr/share/ovlroot"
  install -D -m 644 "$srcdir/ovlroot.sh" "$pkgdir/usr/share/ovlroot/ovlroot.sh"
  install -D -m 444 "$srcdir/ovlroot-helper" "$pkgdir/usr/share/ovlroot/ovlroot-helper"
  install -d -m 700 -o root -g root "$pkgdir/etc/ovlroot.d"
}