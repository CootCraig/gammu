%define name gnokii
%define version 0.4.0pre3
%define release 1

Summary: Linux/Unix tool suite for Nokia mobile phones
Name: %{name}
Version: %{version}
Release: %{release}
Copyright: GPL
Packager: Pavel Janik ml. <Pavel.Janik@linux.cz>, Jan Derfinak <ja@mail.upjs.sk>
Group: Applications/Communications
Source: ftp://ftp.gnokii.org/pub/gnokii/%{name}-%{version}.tar.gz
BuildRoot: /var/tmp/%{name}-%{version}-root

%description
Gnokii is a Linux/Unix tool suite and (eventually) modem/fax driver for
Nokia's mobile phones, released under the GPL.

%package xgnokii
Summary: Graphical Linux/Unix tool suite for Nokia mobile phones.
Group: X11/Applications
%description xgnokii
Xgnokii is graphical Linux/Unix tool suite for Nokia's mobile phones. It
allows you to edit your contacts book, send/read SMS's from/in
computer and more other features.

%prep

%setup -q

%build
./configure --prefix=/usr --with-x --enable-nls #--enable-debug --enable-rlpdebug
make

%install
rm -rf ${RPM_BUILD_ROOT}

make prefix=${RPM_BUILD_ROOT}/usr install

mkdir -p ${RPM_BUILD_ROOT}/etc/

sed 's#/usr/local/sbin/#/usr/sbin/#' <Docs/sample/gnokiirc >${RPM_BUILD_ROOT}/etc/gnokiirc

%pre
/usr/sbin/groupadd -r -f gnokii >/dev/null 2>&1

%postun
/usr/sbin/groupdel gnokii >/dev/null 2>&1

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root)
%doc Docs/CREDITS Docs/DataCalls-QuickStart Docs/FAQ Docs/README
%doc Docs/README-3810 Docs/README-6110 Docs/README-2110 Docs/README-WIN32
%doc Docs/gettext-howto Docs/gnokii.nol Docs/gnokii-ir-howto Docs/packaging-howto
%doc Docs/README-dancall Docs/logos.txt Docs/gnokii.xpm Docs/Bugs
%doc Docs/sample/gnokiirc Docs/sample/options Docs/sample/pap-secrets
%doc Docs/sample/ppp-gnokii Docs/sample/ppp-on
%doc Docs/protocol/nk2110.txt Docs/protocol/nk3110.txt Docs/protocol/nk6110.txt Docs/protocol/nk6160.txt
%doc Docs/protocol/nk6185.txt Docs/protocol/nk640.txt Docs/protocol/nk7110.txt Docs/protocol/nokia.txt
%attr(0750, root, gnokii) /usr/bin/gnokii
%attr(0750, root, gnokii) /usr/sbin/gnokiid
%attr(4750, root, gnokii) /usr/sbin/mgnokiidev
%config /etc/gnokiirc

%files xgnokii
%defattr(-,root,root)
/usr/X11R6/bin/xgnokii
/usr/bin/todologo
/usr/share/xgnokii

%changelog

* Fri Sep 28 2001 Pawel Kot <pkot@linuxnews.pl>
- last minute fixes.

* Thu Sep 27 2001 Pawel Kot <pkot@linuxnews.pl>
- updates to 0.3.3 version - new docs, new ftp server

* Sun Sep  2 2001 Pawel Kot <pkot@linuxnews.pl>
- removes xlogos

* Thu Jan 11 2001 Pawel Kot <pkot@linuxnews.pl>
- misc updates

* Fri Oct 27 2000 Pavel Janik ml. <Pavel.Janik@linux.cz>
- todologo added to the package

* Mon May 15 2000 Pavel Janik ml. <Pavel.Janik@linux.cz>
- proper access rights for gnokiid, gnokii and mgnokiidev

* Sat May 13 2000 Pavel Janik ml. <Pavel.Janik@linux.cz>
- new doc files added

* Tue Mar 21 2000 Pavel Janik ml. <Pavel.Janik@linux.cz>
- permission on /usr/sbin fixed
- correct /etc/gnokiirc file

* Mon Mar 20 2000 Pavel Janik ml. <Pavel.Janik@linux.cz>
- mkdir of directories in install removed
- xgnokii package should contain lib/xgnokii directory

* Mon Mar 20 2000 Jan Derfinak <ja@mail.upjs.sk>
- split package into gnokii and xgnokii
- added configure
- correct xgnokii installation
- installation with make install
- fixing paths

* Thu Aug  5 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- documentation files changed

* Thu Aug  5 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- xkeyb and xlogos added to RPM package

* Sat Jul 24 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- stripping of binaries

* Thu Jul 22 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- gnokii.nol added - nice example for logo uploading

* Sun Jul 18 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- mgnokiidev added to RPM package
- config file in /etc (it is not used now...)

* Sat Jul 10 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- use of ~/.gnokiirc so not magic model stuff
- new doc files

* Mon Jun 28 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- Nokia auth. protocol is there now
- xgnokii and gnokiid added to RPM

* Sun May  9 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- included 6110-patch updated to my prepatches

* Thu May  6 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- TODO-6110 file added to documentation files

* Sun Mar 28 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- upgraded to gnokii-0.2.4
- 6110 version of gnokii added

* Fri Mar  5 1999 Pavel Janik ml. <Pavel.Janik@linux.cz>
- the first SPEC file for gnokii
