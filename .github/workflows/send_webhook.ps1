$url = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"

$jsonBody = @{
    content = "A new build is available"
} | ConvertTo-Json

Invoke-RestMethod -Uri $url -Method Post -Headers @{"Content-Type" = "application/json"} -Body $jsonBody



# https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6