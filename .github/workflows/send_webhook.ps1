# Settings webhook url
$url = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"

# Settings card content
$title       = 'Greetings from powershell'
$description = 'This is an embed. It looks much nicer than just sending text over !'
$color       = '4289797'

$thumbnailObject = [PSCustomObject]@{
    url = "https://cdn.discordapp.com/attachments/1065694223875199080/1175404890885988413/unicorn.jpg?ex=656b1c1b&is=6558a71b&hm=1195df7a323d783fa72e8d0e31708fc234596331d772b08a28502808ffce9378&"
}

# $image = [PSCustomObject]@{
#     url = 'attachment://unicorn.jpg'
# }

# $fileObject = [PSCustomObject]@{
#     attachment = ''
#     name = 'webhook_resized.png'
# }

# Creating emmbed card object
$embedObject = [PSCustomObject]@{
    color = $color
    title = $title
    description = $description
    thumbnail = $thumbnailObject
}

# Creating embed array 
[System.Collections.ArrayList]$embedArray = @()
# Adding to embed to array
$embedArray.Add($embedObject)

# # Creating files array 
# [System.Collections.ArrayList]$filesArray = @()
# # Adding to file to array
# $filesArray.Add($fileObject)

$payload = [PSCustomObject]@{
    embeds = $embedArray
}

# Sending the webhook
Invoke-RestMethod -Uri $url -Method Post -Headers @{"Content-Type" = "application/json"} -Body ($payload | ConvertTo-Json -Depth 4)