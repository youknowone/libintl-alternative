//
//  libintl.h
//  libintl
//
//  Created by Jeong YunWon on 12. 10. 25..
//  Copyright (c) 2012 youknowone.org. All rights reserved.
//

/*
 *  Project: 
 *
 *  This file is used to replace libintl part of gettext runtime with
 *      NSBundle localizedString: for OSX/iOS.
 *  Visit gettext ( http://www.gnu.org/software/gettext/gettext.html ) for
 *  original implementation.
 *
 *  NOTE: This implementation does full-support gettext and dgettext only.
 *      And also support ngettext and dngettext with only singler/plural.
 *      You should use original gettext for the best.
 *
 *  Honor your unix-based i18n code without gettext dependency!
 *  On compile time:
 *      1. Set this dummy libintl.h be header path.
 *      2. Link you project to this dummy libintl.a
 *  On build time:
 *      1. Bundle your <domain>.strings localization files in <locale>.lproj
 *      2. Oops, no .strings files? Here is po_to_strings.rb in repository!
 *  On run time:
 *      1. Be lazy and see your gettext-based code is localized very well!
 *
 *  NOTE: Only system locale is supported.
 */

#include <xlocale.h>

//! @brief Fake gettext version 0.18.1
#ifndef LIBINTL_VERSION
#define LIBINTL_VERSION 0x001201
#endif
extern int libintl_version;

#ifdef __cplusplus
extern "C" {
#endif

//! @note Mapped to NSLocalizedStringFromTable with table from textdomain
extern char *libintl_gettext (const char *__msgid);
//! @note Mapped to NSLocalizedStringFromTable
extern char *libintl_dgettext(const char *__domainname, const char *__msgid);
//! @note Dummy implementation! Category would be ignored always!
extern char *libintl_dcgettext (const char *__domainname, const char *__msgid,
                                int __category);
//! @note Rough implementation! Only for singular/plural form for all locales!
extern char *libintl_ngettext (const char *__msgid1, const char *__msgid2,
                               unsigned long int __n);
//! @note Rough implementation! Only for singular/plural form for all locales!
extern char *libintl_dngettext (const char *__domainname,
                                const char *__msgid1, const char *__msgid2,
                                unsigned long int __n);
//! @note Dummy implementation! Category would be ignored always! Rough implementation! Only for singular/plural form for all locales!
extern char *libintl_dcngettext (const char *__domainname,
                                 const char *__msgid1, const char *__msgid2,
                                 unsigned long int __n, int __category);

extern char *libintl_textdomain (const char *__domainname);
//! @note Dummy implementation! This returns input __dirname with no processing.
extern char *libintl_bindtextdomain (const char *__domainname,
                                     const char *__dirname);
//! @note Dummy implementation! This returns input __dirname with no processing.
extern char *libintl_bind_textdomain_codeset (const char *__domainname,
                                              const char *__codeset);

static inline char *gettext (const char *__msgid)
{
    return libintl_gettext (__msgid);
}
static inline char *dgettext(const char *__domainname, const char *__msgid) {
    return libintl_dgettext(__domainname, __msgid);
}
static inline char *dcgettext (const char *__domainname, const char *__msgid,
                               int __category) {
    return libintl_dcgettext(__domainname, __msgid, __category);
};
static inline char *ngettext (const char *__msgid1, const char *__msgid2,
                              unsigned long int __n) {
    return libintl_ngettext(__msgid1, __msgid2, __n);
}
static inline char *dngettext (const char *__domainname,
                               const char *__msgid1, const char *__msgid2,
                               unsigned long int __n) {
    return libintl_dngettext(__domainname, __msgid1, __msgid2, __n);
}
static inline char *dcngettext (const char *__domainname,
                                const char *__msgid1, const char *__msgid2,
                                unsigned long int __n, int __category) {
    return libintl_dcngettext(__domainname, __msgid1, __msgid2, __n, __category);
}
static inline char *textdomain (const char *__domainname) {
    return libintl_textdomain(__domainname);
}
static inline char *bindtextdomain (const char *__domainname,
                                    const char *__dirname) {
    return libintl_bindtextdomain(__domainname, __dirname);
}
static inline char *bind_textdomain_codeset (const char *__domainname,
                                             const char *__codeset) {
    return libintl_bind_textdomain_codeset(__domainname, __codeset);
}


//! @brief Redirect to setlocale
extern char *libintl_setlocale (int, const char *);
//! @brief Redirect to newlocale
extern locale_t libintl_newlocale (int, const char *, locale_t);
//! @note Dummy implementation! This funciton does nothing.
extern void libintl_set_relocation_prefix (const char *orig_prefix,
                                           const char *curr_prefix);

#ifdef __cplusplus
}
#endif
