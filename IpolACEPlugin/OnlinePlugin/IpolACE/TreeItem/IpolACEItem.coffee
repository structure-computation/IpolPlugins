#
class IpolACEItem extends TreeItem_Computable
    constructor: ( name = "IpolACE" ) ->
        super()

        @add_attr
            alpha   : new ConstrainedVal( 5.0, { min: 1.0, max: 8.0 } )
            weight  : new Choice
            method  : new Choice
        
        radial   = new RadialWeight
        constant = new ConstantWeight
        gaussian = new GaussianWeight
        @weight.lst.push radial
        @weight.lst.push constant
        @weight.lst.push gaussian
        
        interp = new InterpolateMethod
        poly   = new PolynomialMethod
        @method.lst.push interp
        @method.lst.push poly
        
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

