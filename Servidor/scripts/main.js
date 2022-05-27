$("#itens_tabela").on("submit", function(event){
    event.preventDefault(); //this prevents the form to use default submit
 
     $.ajax({
         method: "POST",
         url: $(this).attr("action"), //this will use the form's action attribute
         data: {populate_table: $("#itens_tabela").val()},
         success: function(responseData) {
             let res = JSON.stringify(responseData);
 
             let response = eval(responseData);
 
             let table = document.createElement('table');
 
             for(let i = 0; i < response.length; i++) {
                 // builds header
                 if(i === 0) {
                     let tr = table.insertRow();
                     for(let key in response[i]) {
                         let td = tr.insertCell();
                         let bold = document.createElement('strong');
                         let some_node = document.createTextNode(key);
                         bold.appendChild(some_node);
                         td.appendChild(bold);
                     }
                 }
                 // builds rest
                 let tr = table.insertRow();
                 for(let key in response[i]) {
                     let td = tr.insertCell();
                     td.appendChild(document.createTextNode(response[i][key]));
                 }
             }
             $('#first_task_response_table').html(table);
         }
     });
 });