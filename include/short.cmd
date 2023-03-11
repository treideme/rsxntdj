/* short.cmd */

'@echo off'

call RxFuncAdd 'SysLoadFuncs', 'RexxUtil', 'SysLoadFuncs'
call SysLoadFuncs

if SysSearchPath('PATH', 'sed.exe') == '' then do
  say 'sed.exe not found -- see INSTALL.DOC'
  exit
end

do while lines('longshrt.ls2')
  file = translate(linein('longshrt.ls2'), '\', '/')
  if stream(file, 'C', 'QUERY EXISTS') \= '' then do
    say 'Patching' file
    'sed -f short.sed >tmp' file
    if rc \= 0 then do
      say 'sed failed!'
      exit
    end
    'touch -r' file 'tmp'
    'del' file
    'move tmp' file '>nul'
  end
end

say 'Renaming files'
do while lines('longshrt.ls1')
  line = linein('longshrt.ls1')
  parse var line long short
  file = translate(long, '\', '/')
  if stream(file, 'C', 'QUERY EXISTS') \= '' then
    'ren' file short
end

say 'Done'
