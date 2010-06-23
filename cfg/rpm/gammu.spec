%define ver      0.89.0.0
%define rel      1

Summary: 	 Mobile phones tools for Unix (Linux) and Win32
Name: 		 gammu
Version: 	 %ver
Release: 	 %rel
License: 	 GPL
Group:		 Applications/Communications
Packager:	 Marcin Wiacek <marcin@mwiacek.com>
Source: 	 %name-%{version}.tar.gz
URL:		 http://www.mwiacek.com
Buildroot: 	 %{_tmppath}/%{name}-%{version}-root

%description
Gammu can do such things with cellular phones as making data calls,
updating the address book, changing calendar and ToDo entries, sending and
receiving SMS messages, loading and getting ring tones and pictures (different
types of logos), synchronizing time, enabling NetMonitor, managing WAP
settings and bookmarks and much more. Functions depend on the phone model.

%package devel
Summary:      Development files for Gammu
Group:        Hardware/Mobile
Autoreqprov:  on
Requires:     gammu = %{ver}-%{rel}

%description devel
Gammu can do such things with cellular phones as making data calls,
updating the address book, changing calendar and ToDo entries, sending and
receiving SMS messages, loading and getting ring tones and pictures (different
types of logos), synchronizing time, enabling NetMonitor, managing WAP
settings and bookmarks and much more. Functions depend on the phone model.

%prep
%setup -q

%build
%configure --with-docdir=%_defaultdocdir/gammu/
make makelib

%install
rm -rf $RPM_BUILD_ROOT
make installlib DESTDIR=$RPM_BUILD_ROOT
install -m 755 -d $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/config
install -m 755 -d $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/basic
install -m 755 -d $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/smsdutil
install -m 755 other/config/gammu-config $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/config
install -m 644 other/basic/* $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/basic
install -m 644 other/smsdutil/* $RPM_BUILD_ROOT%_defaultdocdir/gammu/other/smsdutil

%files
%defattr(-,root,root)
%_bindir/*
%_libdir/libGammu*
#localisations:
/usr/share/gammu
%doc %_mandir/man1/*
%doc %_defaultdocdir/gammu

%files devel
%defattr(-,root,root)
%_includedir/gammu
%_libdir/pkgconfig/gammu.pc

%clean
rm -rf $RPM_BUILD_ROOT

%changelog
* Mon Nov 03 2003 Michal Cihar <michal@cihar.com>
- split devel package

* Thu Jan 02 2003 Michal Cihar <michal@cihar.com>
- made it install in directories that are defined in rpm

* Sun Nov 10 2002 Marcin Wiacek <marcin@mwiacek.com>
- topnet.pl email no more available

* Sun Sep 30 2002 Marcin Wiacek <marcin-wiacek@topnet.pl>
- build system is now really working OK

* Sat Sep 15 2002 R P Herrold <herrold@owlriver.com>
- initial packaging
