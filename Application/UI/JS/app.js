/************************************************** Description *******************************************************/
/*
    File : app.js
    Programmer : Mohammad Lotfi
    Used : application
    Design Pattern : Nothing
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2024/11/17
*/
/************************************************** Warnings **********************************************************/
/*
    Nothing
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
/*
    Nothing
*/
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
function Refresh() {
	$("#Main").html("Loading...");
	Execute("", "Login", "", 10000).then(function (response) {        
        $("#Main").html(response);
    }).catch(function (response) {
		$("#Main").html("Failed");
	});
}
/*--------------------------------------------------------------------------------------------------------------------*/
// Function to get and set data of device by the IP address
function Execute(IpAddress, Command, Value, TimeOut) {
    return new Promise(async function (resolve, reject) {
        var StructData = {
			Username: "admin",
			Password: "admin",
            IpAddress: IpAddress,
            Command: Command,
            Value: Value,
            TimeOut: TimeOut
        };
        $.ajax({
            type: "GET",
            url: "Execute.dll",
            data: JSON.stringify({ inputdata: StructData }),
            contentType: "application/json; charset=utf-8",
            dataType: "json",
            success: function (response) {
                resolve(response.d);
            },
            error: function (xhr, textStatus, errorThrown) {
                reject(errorThrown);
            }
        });
    });
}
/*--------------------------------------------------------------------------------------------------------------------*/
function Toast(Text) {
	//$("#Alert").html(Text);
	setTimeout(function(){
		//$("#Alert").html('');
	}, 2000);
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/


