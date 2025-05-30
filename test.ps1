$file = "./config.xml"
[xml]$xml = Get-Content -Path $file
$env:VERSION = $xml.VBContent.version
return $env:VERSION