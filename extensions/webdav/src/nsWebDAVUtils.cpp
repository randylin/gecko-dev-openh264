/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
// vim:expandtab:ts=4 sw=4:
/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is Mozilla.
 *
 * The Initial Developer of the Original Code is Oracle Corporation.
 * Portions created by Oracle Corporation are  Copyright (C) 2004
 * by Oracle Corporation.  All Rights Reserved.
 *
 * Contributor(s):
 *   Mike Shaver <shaver@off.net> (original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsWebDAVInternal.h"

#include "nsIDOMElement.h"
#include "nsIDOMNode.h"
#include "nsIDOM3Node.h"
#include "nsIDOMNodeList.h"

#if defined(PR_LOGGING)
PRLogModuleInfo *gDAVLog = nsnull;
#endif

nsresult
NS_WD_GetElementByTagName(nsIDOMElement *parentElt, const nsAString &tagName,
                          nsIDOMElement **elt)
{
    nsresult rv;

    nsCOMPtr<nsIDOMNodeList> list;
    rv = parentElt->GetElementsByTagName(tagName, getter_AddRefs(list));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIDOMNode> node;
    rv = list->Item(0, getter_AddRefs(node));
    NS_ENSURE_SUCCESS(rv, rv);

    return CallQueryInterface(node, elt);
}

nsresult
NS_WD_ElementTextChildValue(nsIDOMElement *elt, const nsAString &tagName,
                            nsAString &value)
{
    nsCOMPtr<nsIDOMElement> childElt;
    nsresult rv = NS_WD_GetElementByTagName(elt, tagName,
                                            getter_AddRefs(childElt));
    NS_ENSURE_SUCCESS(rv, rv);

    nsCOMPtr<nsIDOM3Node> node3 = do_QueryInterface(childElt, &rv);
    NS_ENSURE_SUCCESS(rv, rv);

    return node3->GetTextContent(value);
}

