#
class IpolSCAItem extends TreeItem_Computable
    constructor: ( name = "IpolSCA" ) ->
        super()

        @add_attr
            thresold                : new ConstrainedVal( 50, { min: 0.0 } )
            gradient_amplification  : new ConstrainedVal( 3.0, { min: 0.01 } )
            gradient_power          : new ConstrainedVal( 0.8, { min: 0.01 } )
            algorithm : new Choice(0,["simple gray","local gray","global gray","simple rgb","local rgb","global rgb"])
        
        @_name.set name
        #@_ico.set "img/scilab.png"
        @_viewable.set false
        @_computation_mode.set false
        
        @add_child new ImgSetItem 'input'
        @add_output new ImgSetItem 'output'
        
        
    get_model_editor_parameters: ( res ) ->
        res.model_editor[ "weight" ] = ModelEditorItem_ChoiceWithEditableItems
        res.model_editor[ "method" ] = ModelEditorItem_ChoiceWithEditableItems
    
    accept_child: ( ch ) ->
        ch instanceof ImgItem or
        ch instanceof FileItem
        
    is_app_data: ( item ) ->
        if item instanceof TreeAppData
            return true
        else
            return false
        
    #get app.data
    get_app_data: ->
        #get app_data
        it = @get_parents_that_check @is_app_data
        return it[ 0 ]
        
    do_it: ->
        app_data = @get_app_data()
        for child in @_output[0]._children
            @_output[0].rem_child child
            app_data.delete_from_tree child
        TreeItem_Computable._do_it_rec this
    
    z_index: ->
        #

