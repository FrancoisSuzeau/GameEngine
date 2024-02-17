# Settings webhook url
$discordWebhookUrl = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"
$WEBHOOK_URL = "https://discord.com/api/webhooks/1171550224045576224/fWJf83DLoXugzWao-KxdEq-NwfgyCh0fmEA4Jdwtqdwomke5c5o17Vne7o90M6FYWxf6"
$username = "Github Webhook"
$webhook_content = "You might want to take a look .."
$authorObject = [PSCustomObject]@{
    name = $args[0]
    url = "https://github.com/FrancoisSuzeau"
    icon_url = $args[1]
}

# Settings card content
$title       = 'Squeamish : New merge done'
$description = 'A recent merge was made in the Squeamish project ! 
It could be interesting to take a look and give us your feelback.
:wink:

**What is new :**'
$color       = '4289797'
# Create thumbnail object with a jpg availabe in a discord channel -> see later if it is perrene
$thumbnailObject = [PSCustomObject]@{
    url = "https://cdn.discordapp.com/attachments/1065694223875199080/1175404890885988413/unicorn.jpg?ex=656b1c1b&is=6558a71b&hm=1195df7a323d783fa72e8d0e31708fc234596331d772b08a28502808ffce9378&"
}

# Getting labels
[System.Collections.ArrayList]$lblArray = $args[3]
$labels = ""
if($lblArray.Count -ne 0)
{
    foreach($elem in $lblArray.ToArray())
    {
        $labels += $elem + ", "
    }
    
}

# Creating fields array 
[System.Collections.ArrayList]$fieldsArray = @()

# Creating 1st field -> feature release
$field1 = [PSCustomObject]@{
    name = ':unicorn: ' +  "**" + $args[2] + "**"
    value = "*" + $labels + "*"
    inline = "true"
}

# add first field
$return = $fieldsArray.Add($field1)

# Creating 2nd field -> issue linked
$field2 = [PSCustomObject]@{
    name = ':wave: ' +  "**Issue linked**"
    value = "[" + $args[4] + "](" + $args[5] + ")"
    inline = "true"
}

# add first field
$return = $fieldsArray.Add($field2)

# Creating footer
$footerContent = [PSCustomObject]@{
    text = 'Woah! So cool!'
}
# Creating emmbed card object
$embedObject = [PSCustomObject]@{
    author= $authorObject
    color = $color
    title = $title
    url = "https://github.com/FrancoisSuzeau/Squeamish"
    description = $description
    thumbnail = $thumbnailObject
    fields = $fieldsArray.ToArray()
    footer = $footerContent
} 
# Creating embed array 
[System.Collections.ArrayList]$embedArray = @()
# Adding to embed to array
$return = $embedArray.Add($embedObject)

# Create payload
$payload = [PSCustomObject]@{
    username = $username
    content = $webhook_content
    embeds = $embedArray
}

try {
    #http $WEBHOOK_URL username=$username content=$webhook_content embeds=$embedArray --ignore-stdin
    Invoke-RestMethod -Uri $WEBHOOK_URL -Method Post -Headers @{"Content-Type" = "application/json"} -Body ($payload | ConvertTo-Json -Depth 4)
}
catch {
    Write-Host "Error: $_"
}

