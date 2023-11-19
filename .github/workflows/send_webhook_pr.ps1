# Settings webhook url
$discordWebhookUrl = "https://discord.com/api/webhooks/1175831319079555195/kcwebNYUIHrkI16dM7qS9E3OVmESIlAFmb0fphEzoGuERZSDIGU4jY9DTeQrvYN_KRU1"
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
# Creating fields array 
[System.Collections.ArrayList]$fieldsArray = @()
# Creating 1st field -> feature release
$field1 = [PSCustomObject]@{
    name = ':unicorn:  ' + $args[2]
    value = $args[3]
    inline = "false"
}
$fieldsArray.Add($field1)
# Creating footer
$footerContent = [PSCustomObject]@{
    text = 'Woah! So cool!'
}
# Creating emmbed card object
$embedObject = [PSCustomObject]@{
    color = $color
    author = $authorObject
    title = $title
    url = "https://github.com/FrancoisSuzeau/Squeamish"
    description = $description
    thumbnail = $thumbnailObject
    fields = $fieldsArray
    footer = $footerContent
}
# Creating embed array 
[System.Collections.ArrayList]$embedArray = @()
# Adding to embed to array
$embedArray.Add($embedObject)
# Create payload
$payload = [PSCustomObject]@{
    username = $username
    content = $webhook_content
    embeds = $embedArray
}
# Sending the webhook
Invoke-RestMethod -Uri $discordWebhookUrl -Method Post -Headers @{"Content-Type" = "application/json"} -Body ($payload | ConvertTo-Json -Depth 4)