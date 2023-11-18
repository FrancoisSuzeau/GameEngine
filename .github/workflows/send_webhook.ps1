# Settings webhook url
$url = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"

# Settings card content
$title       = 'Greetings from powershell'
$description = 'This is an embed. It looks much nicer than just sending text over !'
$color       = '4289797'

$thumbnailObject = [PSCustomObject]@{
    url = "https://github.com/FrancoisSuzeau/Squeamish/blob/feature/CI/.github/workflows/unicorn.PNG"
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