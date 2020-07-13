# AD-Compromised-Passwords

## Installation

 1. Copy DLL to C:\Windows\System32
 2. Set `HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Lsa\Notification Packages` to the name of the DLL (no extension)
 3. Set `HKEY_LOCAL_MACHINE\SOFTWARE\AD-Compromised-Passwords\URI` to the api endpoint. Example: `api.pwnedpasswords.com`
 4. Enable the password requirements policy: `Performace and Maintenance > Administrative Tools > Local Security Policy > Account Policies > Password Policy > **Passwords must meet complexity requirements**` as enabled.
