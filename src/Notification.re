module ReactNotificationSystem = {
    [@bs.module ] external reactClass : ReasonReact.reactClass = "react-notification-system/dist/NotificationSystem";

    let make = ( children ) => 
    ReasonReact.wrapJsForReason(
        ~reactClass, 
        ~props=Js.Obj.empty(),
        children
    )
};

type action =
  | AddNotification(string);

type state = {
    _notificationSystem: ref(option(ReasonReact.reactRef)),
};

let setNotificationSystemRef = (notificationRef, {ReasonReact.state}) => 
  state._notificationSystem := Js.Nullable.to_opt(notificationRef) ;

let component = ReasonReact.reducerComponent("Notifications");

let addNotification = (message, state) => {   
    switch state._notificationSystem^ {
    | None => ()
    | Some(r) => ReasonReact.refToJsObj(r)##addNotification({"message": message, "level": "success"});      
    }
};

let make = (_children) => {
    ...component,
    initialState: () => {_notificationSystem: ref(None) },
    reducer: (action, state) =>
        switch action {
            | AddNotification(message) =>  ReasonReact.SideEffects(((_) => addNotification(message, state)))
        },
    render: ({handle, reduce}) => (
    <div>             
        <ReactNotificationSystem ref=(handle(setNotificationSystemRef)) />
        <button onClick=(reduce( (_) => AddNotification("Hello"))) > (ReasonReact.stringToElement("Click")) </button> 
    </div>
  )
};