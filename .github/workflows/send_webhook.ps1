# Settings webhook url
$url = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"

# Settings card content
$title       = 'Greetings from powershell'
$description = 'This is an embed. It looks much nicer than just sending text over !'
$color       = '4289797'
$thumbnailObject = [PSCustomObject]@{
    url = "https://static1.squarespace.com/static/5644323de4b07810c0b6db7b/t/5aa44874e4966bde3633b69c/1520715914043/webhook_resized.png"
}

# Creating embed array 
[System.Collections.ArrayList]$embedArray = @()

# Creating emmbed card object
$embedObject = [PSCustomObject]@{
    color = $color
    title = $title
    description = $description
    thumbnail = $thumbnailObject
}

# Adding to embed array
$embedArray.Add($embedObject)
$payload = [PSCustomObject]@{
    embeds = $embedArray
}

# Sending the webhook
Invoke-RestMethod -Uri $url -Method Post -Headers @{"Content-Type" = "application/json"} -Body ($payload | ConvertTo-Json -Depth 4)