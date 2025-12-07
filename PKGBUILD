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
pkgver=0.9.4
pkgrel=1
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
  '8ca7360df9a9e781bb8c99505030d5b4c97e9b4bf87ec6d3992ec98c2a0b0e2b'
  'dca9056eb5e460ee6465de921a4b77524ebc7e6a83b964c629be525934910ef0'
  'c6e15e20c35897e653d80a5ce6b3b78700d8ff35052803401bb9b2c214c45bfc'
  'f24f1bfc4bf18732650db7d09bcbbced5631e735e44c760f5ba646811f17ed91'
  'e4c02cb62632cae14024490e7a02371f9291e5f66812a96dca9ffd4aa9517868'
)

build() {
  gcc -o ovlroot-helper "$srcdir/ovlroot-helper.c"
}

package() {
  install -D -m 644 "$srcdir/install.sh" "$pkgdir/usr/lib/initcpio/install/ovlroot"
  install -D -m 644 "$srcdir/hook.sh" "$pkgdir/usr/lib/initcpio/hooks/ovlroot"
  install -D -m 555 "$srcdir/mount.ovlroot" "$pkgdir/usr/bin/mount.ovlroot"
  mkdir -p "$pkgdir/usr/share/ovlroot"
  install -D -m 444 "$srcdir/ovlroot.sh" "$pkgdir/usr/share/ovlroot/ovlroot.sh"
  install -D -m 555 "$srcdir/ovlroot-helper" "$pkgdir/usr/share/ovlroot/ovlroot-helper"
  install -d -m 700 -o root -g root "$pkgdir/etc/ovlroot.d"
}