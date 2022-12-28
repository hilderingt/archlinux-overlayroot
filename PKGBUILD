pkgname=overlayroot
pkgver=1.0
pkgrel=1
pkgdesc="overlayFS root filesystem"
arch=('any')
url="https://github.com/hilderingt/archlinux-overlayroot"
license=('GPLv3')
depends=(
  'mkinitcpio'
)
source=(
  'overlayroot-install.hooks'
  'overlayroot-runtime.hooks'
)
sha256sums=(
  'SKIP'
  'SKIP'
)

build() {
  :
}

package() {
  install -Dm644 "$srcdir/overlayroot-install.hooks" "$pkgdir/usr/lib/initcpio/install/overlayroot"
  install -Dm644 "$srcdir/overlayroot-runtime.hooks" "$pkgdir/usr/lib/initcpio/hooks/overlayroot"
}
