﻿using System;
using System.Data.SqlClient;
using System.Web.UI;

public partial class denglu : Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
    }

    protected void btnOk_Click(object sender, EventArgs e)
    {
        SqlConnection con = DB.createDB();
        SqlCommand cmd = new SqlCommand();
        cmd.Connection = con;
        con.Open();
        cmd.CommandText = "select count(*) from tb_Users where UserName='" + txtyhm.Text + "'and UserPwd='" +
                          txtyhmm.Text + "' ";
        int a = Convert.ToInt32(cmd.ExecuteScalar());
        if (a > 0)
        {
            Session["UserName"] = txtyhm.Text;
            Session["UserPwd"] = txtyhmm.Text;

            Response.Redirect("~/default.aspx");
        }
        else
        {
            Response.Write("<script>alert('很遗憾，登录失败！');location='javascript:history.go(-1)'</script>");
        }
        con.Close();
    }

    protected void LinkButton1_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Default.aspx");
    }

    protected void btncancel_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Default.aspx");
    }

    protected void lbtnsy_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/Default.aspx");
    }

    protected void LinkButton4_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/yonghuxinxi/yonghu.aspx");
    }

    protected void LinkButton5_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/dangqianxinxi/dqyhxinxixg.aspx");
    }

    protected void LinkButton6_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/yonghuxinxi/yonghuchaxun.aspx");
    }

    protected void LinkButton7_Click(object sender, EventArgs e)
    {
        Response.Redirect("~/denglu/denglu.aspx");
    }

    protected void ImageButton2_Click(object sender, ImageClickEventArgs e)
    {
        Response.Redirect("~/teizixinxi/addteizi.aspx");
    }
}