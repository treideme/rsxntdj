/* make.cmd */

if stream('unchecked.h', 'C', 'QUERY EXISTS') == '',
  |stream('cpp\stl_hash_set.h', 'C', 'QUERY EXISTS') == '' then do
  say 'Do not run this procedure now.'
  exit 1
end

'gfind . -type f -print|grep -e "^\(.*/\)*[^/.]\{9,\}\(\.[hc]\|\.cc\|\.hP\|\.ccP\|\)$" >make.$$1'
'sed -f make1.sed make.$$1 >make.$$2'
'sed -f make2.sed make.$$1 >longshrt.ls1'
'gfind . -type f -print|grep -e "^\(.*/\)*[^/.]\+\(\.[hc]\|\.cc|\.hP\|\.ccP\|\)$"|xargs grep -l -f make.$$2 >longshrt.ls2'
'sed -f make3.sed longshrt.ls1 >short.sed'
'sed -f make4.sed longshrt.ls1 >long.sed'
'del make.$$1 make.$$2 >nul'
