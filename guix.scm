(use-modules (guix git)
             (guix packages)
             (guix licenses)
             (guix build-system gnu)
             (gnu packages)
             (gnu packages llvm)
             (gnu packages assembly))

(package
    (name "istar")
    (version "0.0.0")
    (source (git-checkout (url "https://github.com/d0p1s4m4/Istar.git")))
    (build-system gnu-build-system)
    (arguments
        '(#:phases
            (modify-phases %standard-phases
                (delete 'configure))))
    (inputs (list lld clang nasm))
    (home-page "https://github.com/d0p1s4m4/Istar")
    (synopsis "Istar a tiny bootloader")
    (description "A tiny handover bootloader in C and x86 assembly")
    (license bsd-3))
